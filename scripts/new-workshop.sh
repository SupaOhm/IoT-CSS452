#!/usr/bin/env bash
set -euo pipefail

usage() {
  echo "Usage: $0 WorkshopXX [--dry-run]" >&2
  exit 1
}

[[ $# -ge 1 && $# -le 2 ]] || usage
workshop="$1"
dry_run="${2:-}"
[[ "$workshop" =~ ^Workshop[0-9][0-9]$ ]] || { echo "Workshop name must look like Workshop02." >&2; exit 1; }
[[ -z "$dry_run" || "$dry_run" == "--dry-run" ]] || usage

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
workshop_path="$root/$workshop"
folders=(
  "materials/01_lecture-notes"
  "materials/02_example-code"
  "materials/03_in-class-exercises"
  "materials/04_homework"
  "generated"
)

if [[ -d "$workshop_path" ]]; then
  echo "Refusing to overwrite existing folder: $workshop_path" >&2
  exit 1
fi

if [[ "$dry_run" == "--dry-run" ]]; then
  printf 'Would create: %s\n' "$workshop_path"
  printf '  %s\n' "${folders[@]}"
  exit 0
fi

for folder in "${folders[@]}"; do
  mkdir -p "$workshop_path/$folder"
done

touch "$workshop_path/materials/01_lecture-notes/.gitkeep"
touch "$workshop_path/materials/02_example-code/.gitkeep"
touch "$workshop_path/materials/03_in-class-exercises/.gitkeep"
touch "$workshop_path/materials/04_homework/.gitkeep"
touch "$workshop_path/generated/.gitkeep"
echo "Created $workshop. Add your course files under $workshop_path/materials/, then run ./scripts/process-workshop.sh $workshop"
