#!/usr/bin/env bash
# Dropper intake. Deterministic; no model judgement lives in this file.
#
#   intake.sh scan            convert + propose a category for each dropped file
#   intake.sh apply <tsv>     move files into the categories confirmed by Claude
#
# Not part of the documented user workflow: Claude runs this as step 0 of
# "do workshop X". Running it by hand is harmless and idempotent.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
dropper="$root/dropper"
staging="$dropper/_staging"
proposal="$dropper/_intake-proposal.tsv"
CATS="01_lecture-notes 02_example-code 03_in-class-exercises 04_homework"

die() { echo "intake: $*" >&2; exit 1; }

active_workshop() {
  [[ -f "$dropper/.active-workshop" ]] || die "no dropper/.active-workshop. Run ./scripts/set-workshop.sh WorkshopXX"
  local w
  w="$(tr -d '[:space:]' < "$dropper/.active-workshop")"
  [[ "$w" =~ ^Workshop[0-9][0-9]$ ]] || die "dropper/.active-workshop is malformed ('$w'). Run ./scripts/set-workshop.sh WorkshopXX"
  [[ -d "$root/$w" ]] || die "$w does not exist. Run ./scripts/set-workshop.sh $w"
  printf '%s' "$w"
}

sha_of() { shasum -a 256 "$1" | awk '{print $1}'; }

lower() { printf '%s' "$1" | tr '[:upper:]' '[:lower:]'; }

# Non-whitespace character count of a file (0 if absent).
text_weight() {
  [[ -f "$1" ]] || { echo 0; return; }
  tr -d '[:space:]' < "$1" | wc -c | tr -d ' '
}

# Proposed category from extension and name. Proposal only; Claude confirms.
propose_category() {
  local name ext base
  name="$(lower "$(basename "$1")")"
  ext="${name##*.}"
  case "$ext" in
    ino|cpp|c|h|hpp) echo "02_example-code"; return ;;
  esac
  case "$name" in
    *hw*|*homework*|*assign*)                echo "04_homework"; return ;;
    *lab*|*exercise*|*inclass*|*in-class*)   echo "03_in-class-exercises"; return ;;
  esac
  echo "01_lecture-notes"
}

is_native_text() {
  case "$(lower "${1##*.}")" in
    ino|cpp|c|h|hpp|md|txt|csv|json) return 0 ;;
  esac
  return 1
}

# Convert $1 into markdown at $2. Echoes "converter fidelity".
convert_file() {
  local src="$1" out="$2" ext
  ext="$(lower "${src##*.}")"

  if markitdown "$src" > "$out" 2>/dev/null && [[ "$(text_weight "$out")" -ge 20 ]]; then
    echo "markitdown CLEAN"; return 0
  fi

  if [[ "$ext" == "pdf" ]]; then
    # No usable text layer: rasterise and OCR.
    local tmpdir; tmpdir="$(mktemp -d)"
    if pdftoppm -r 300 -png "$src" "$tmpdir/pg" >/dev/null 2>&1; then
      : > "$out"
      local page
      for page in "$tmpdir"/pg-*.png; do
        [[ -e "$page" ]] || continue
        tesseract "$page" - >> "$out" 2>/dev/null || true
      done
      if [[ "$(text_weight "$out")" -ge 20 ]]; then
        rm -rf "$tmpdir"; echo "tesseract OCR"; return 0
      fi
    fi
    rm -rf "$tmpdir"
    if pdftotext -layout "$src" "$out" 2>/dev/null && [[ "$(text_weight "$out")" -ge 20 ]]; then
      echo "pdftotext REDUCED"; return 0
    fi
  fi

  rm -f "$out"
  echo "none FAILED"; return 0
}

manifest_has() {
  local mf="$1" sha="$2"
  [[ -f "$mf" ]] && grep -q "^$sha	" "$mf"
}

# Collision-safe destination path: name.pdf, name-2.pdf, name-3.pdf ...
free_path() {
  local dir="$1" name="$2" stem ext n cand
  case "$name" in
    *.*) stem="${name%.*}"; ext=".${name##*.}" ;;
      *) stem="$name";      ext="" ;;
  esac
  cand="$dir/$name"; n=2
  while [[ -e "$cand" ]]; do
    cand="$dir/$stem-$n$ext"; n=$((n + 1))
  done
  printf '%s' "$cand"
}

# Count files sitting in the dropper root that intake would act on.
droppable_count() {
  local f base n=0
  for f in "$dropper"/*; do
    [[ -f "$f" ]] || continue
    base="$(basename "$f")"
    case "$base" in
      .active-workshop|_intake-proposal.tsv|.gitkeep|.DS_Store) continue ;;
    esac
    n=$((n + 1))
  done
  echo "$n"
}

# A workshop is "finished" once both task sheets have arrived and at least one
# task folder has been generated. Sheets are dropped separately — the exercise
# often lands days before the homework — so a workshop can hold generated tasks
# and still be owed material; advancing the pointer then would file the missing
# sheet into the next workshop. INDEX.md is no evidence at all: it is written as
# soon as any material lands.
has_material() {
  [[ -n "$(find "$root/$1/materials/$2" -mindepth 1 -maxdepth 1 -type f \
             ! -name '.gitkeep' -print -quit 2>/dev/null)" ]]
}

workshop_is_finished() {
  has_material "$1" 03_in-class-exercises || return 1
  has_material "$1" 04_homework || return 1
  [[ -n "$(find "$root/$1/generated" -mindepth 1 -maxdepth 1 -type d \
             \( -name 'P[0-9]*' -o -name 'Exercise[0-9]*' \) -print -quit 2>/dev/null)" ]]
}

cmd_scan() {
  local workshop; workshop="$(active_workshop)"

  # Guard against the pointer being left on a completed workshop: new files
  # dropped after a workshop is done almost always belong to the next one.
  if [[ "$(droppable_count)" -gt 0 ]] && workshop_is_finished "$workshop"; then
    echo "NOTE: $workshop already has generated output, but files are waiting in the dropper." >&2
    "$root/scripts/advance-workshop.sh" >&2
    workshop="$(active_workshop)"
    echo "NOTE: filing into $workshop instead. To override, run ./scripts/set-workshop.sh <name> and scan again." >&2
  fi
  local mdir="$root/$workshop/materials"
  local manifest="$mdir/.intake-manifest.tsv"
  mkdir -p "$staging" "$dropper/_unsorted"
  : > "$proposal"

  local found=0 f base sha staged conv fid result dest
  for f in "$dropper"/*; do
    [[ -f "$f" ]] || continue
    base="$(basename "$f")"
    case "$base" in
      .active-workshop|_intake-proposal.tsv|.gitkeep|.DS_Store) continue ;;
    esac
    found=$((found + 1))
    sha="$(sha_of "$f")"

    if manifest_has "$manifest" "$sha"; then
      printf '%s\t%s\t%s\t%s\t%s\t%s\n' "$sha" "$base" "DUPLICATE" "-" "DUPLICATE" "-" >> "$proposal"
      continue
    fi

    if is_native_text "$base"; then
      conv="none"; fid="NATIVE"; staged="-"
    else
      staged="$staging/$sha.md"
      result="$(convert_file "$f" "$staged")"
      conv="${result%% *}"; fid="${result##* }"
      [[ "$fid" == "FAILED" ]] && staged="-"
    fi

    if [[ "$fid" == "FAILED" ]]; then
      dest="$(free_path "$dropper/_unsorted" "$base")"
      mv "$f" "$dest"
      printf '%s\t%s\t%s\t%s\t%s\t%s\n' "$sha" "$base" "_unsorted" "$conv" "$fid" "-" >> "$proposal"
      continue
    fi

    printf '%s\t%s\t%s\t%s\t%s\t%s\n' \
      "$sha" "$base" "$(propose_category "$base")" "$conv" "$fid" "$staged" >> "$proposal"
  done

  if [[ "$found" -eq 0 ]]; then
    echo "NOTHING_TO_INTAKE workshop=$workshop"
    return 0
  fi
  echo "PROPOSAL workshop=$workshop file=$proposal"
  cat "$proposal"
}

# apply <decisions.tsv>  with lines: <sha> <TAB> <final-category>
cmd_apply() {
  local decisions="${1:-}"
  [[ -n "$decisions" && -f "$decisions" ]] || die "apply needs a decisions TSV (sha<TAB>category)"
  [[ -f "$proposal" ]] || die "no proposal found; run 'intake.sh scan' first"

  local workshop; workshop="$(active_workshop)"
  local mdir="$root/$workshop/materials"
  local manifest="$mdir/.intake-manifest.tsv"
  [[ -f "$manifest" ]] || printf '# sha256\toriginal\tcategory\tconverter\tfidelity\tstored_as\n' > "$manifest"

  local sha base prop conv fid staged final ok dest cdir moved=0
  while IFS="$(printf '\t')" read -r sha base prop conv fid staged; do
    [[ -n "${sha:-}" ]] || continue
    [[ "$fid" == "DUPLICATE" || "$fid" == "FAILED" ]] && continue

    final="$(awk -F'\t' -v s="$sha" '$1==s {print $2; exit}' "$decisions")"
    [[ -n "$final" ]] || die "no decision for $base ($sha)"

    ok=0
    for c in $CATS; do [[ "$c" == "$final" ]] && ok=1; done
    if [[ "$final" == "_unsorted" ]]; then
      dest="$(free_path "$dropper/_unsorted" "$base")"
      [[ -f "$dropper/$base" ]] && mv "$dropper/$base" "$dest"
      continue
    fi
    [[ "$ok" -eq 1 ]] || die "unknown category '$final' for $base"

    cdir="$mdir/$final"
    mkdir -p "$cdir/.converted"
    dest="$(free_path "$cdir" "$base")"
    [[ -f "$dropper/$base" ]] || die "$base vanished from the dropper between scan and apply"
    mv "$dropper/$base" "$dest"

    if [[ "$staged" != "-" && -f "$staged" ]]; then
      mv "$staged" "$cdir/.converted/$(basename "$dest").md"
    fi

    printf '%s\t%s\t%s\t%s\t%s\t%s\n' \
      "$sha" "$base" "$final" "$conv" "$fid" "${dest#$root/}" >> "$manifest"
    moved=$((moved + 1))
  done < "$proposal"

  rm -f "$proposal"
  rmdir "$staging" 2>/dev/null || true
  write_intake_md "$workshop" "$manifest"
  echo "APPLIED workshop=$workshop moved=$moved manifest=${manifest#$root/}"
}

# Human-readable provenance log, regenerated from the manifest each apply.
write_intake_md() {
  local workshop="$1" manifest="$2" out="$root/$workshop/materials/INTAKE.md"
  {
    echo "# $workshop — intake log"
    echo
    echo "Generated by \`scripts/intake.sh\`. Originals are the source of truth;"
    echo "files under \`.converted/\` are extracted text used for reading only."
    echo
    echo "| Original | Category | Converter | Fidelity | Stored as |"
    echo "| --- | --- | --- | --- | --- |"
    awk -F'\t' 'NR>1 && NF>=6 { printf("| `%s` | %s | %s | **%s** | `%s` |\n", $2, $3, $4, $5, $6) }' "$manifest"
    echo
    echo "## Fidelity and what it permits"
    echo
    echo "| Grade | Meaning | Constraint on generated work |"
    echo "| --- | --- | --- |"
    echo "| \`NATIVE\` | text file read directly | facts usable normally |"
    echo "| \`CLEAN\` | markitdown structured output | facts usable normally |"
    echo "| \`REDUCED\` | pdftotext fallback; layout and tables lost | pin tables, wiring figures, and column-aligned values must raise QUESTIONS.md |"
    echo "| \`OCR\` | tesseract on a scanned page | GPIO numbers, resistor values, and timings must raise QUESTIONS.md |"
    echo "| \`FAILED\` | unconvertible; left in \`dropper/_unsorted/\` | dependent tasks are NEEDS CLARIFICATION |"
    if [[ -n "$(ls -A "$dropper/_unsorted" 2>/dev/null | grep -v '^\.gitkeep$' || true)" ]]; then
      echo
      echo "## Quarantined (needs your decision)"
      echo
      local q
      for q in "$dropper"/_unsorted/*; do
        [[ -f "$q" ]] || continue
        [[ "$(basename "$q")" == ".gitkeep" ]] && continue
        echo "- \`$(basename "$q")\` — could not be converted; not filed into any category."
      done
    fi
  } > "$out"
}

case "${1:-}" in
  scan)  cmd_scan ;;
  apply) shift; cmd_apply "${1:-}" ;;
  *)     echo "Usage: $0 {scan|apply <decisions.tsv>}" >&2; exit 1 ;;
esac
