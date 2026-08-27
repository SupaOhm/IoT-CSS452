# Dropper Intake Pipeline — Design

Date: 2026-08-27
Status: Approved (design); not yet implemented
Repo: SupaOhm/IoT-CSS452

## Problem

Course material arrives as mixed files (PDF lecture slides, `.pptx` decks, `.docx`
handouts, instructor `.ino` examples). Today the student must hand-file each one
into the correct `WeekXX/materials/` category folder, and Claude must read PDFs
directly — which is unreliable and, under the repository's evidence-first rules,
risky.

This design adds a single drop point, a deterministic conversion step, and a
model-confirmed classification step, so that one command (`do week 02`) takes raw
supplied files all the way to reviewable `.ino` solutions.

## Decisions

| # | Decision | Chosen | Rejected alternatives |
|---|---|---|---|
| 1 | Week routing | `dropper/.active-week` pointer file | dropper subfolders; content inference; filename prefixes |
| 2 | Classification | Extension rules propose, Claude confirms from converted text, `_unsorted/` quarantine | pure filename rules; full model classification |
| 3 | Converter | `markitdown` primary, `tesseract` OCR for scans, `pdftotext -layout` fallback | opendataloader-pdf (PDF-only); both engines; pdftotext alone |
| 4 | Trigger | Intake runs only as step 0 of `do week X` | standalone command; both; background watcher |
| 5 | Sketch filename | `P1/P1.ino`, `HW1/HW1.ino` | nested `solution/solution.ino`; keep `solution.ino` |

Decision 5 supersedes the `solution.ino` requirement in `CLAUDE.md`. Rationale:
the Arduino IDE requires a sketch's `.ino` filename to match its parent folder
name, and refuses to open a mismatched sketch without relocating the file.

## Environment (verified 2026-08-27)

| Tool | State | Role |
|---|---|---|
| `markitdown` | not installed; PyPI 0.1.7 | primary converter — install via `pipx install 'markitdown[all]'` |
| `opendataloader-pdf` | not installed; PyPI 2.5.5 | not used (PDF-only; no `.pptx`/`.docx`) |
| `pdftotext` | installed (`/opt/homebrew/bin`) | fallback converter |
| `tesseract` | installed (`/opt/homebrew/bin`) | OCR for scanned PDFs |
| `java` | Temurin JDK 21.0.3 | unused by the chosen design |
| LibreOffice | absent | why `markitdown` is required for Office formats |

## Layout

```text
dropper/
├── .active-week              # single line, e.g. "Week02"
├── _unsorted/                # quarantine: unconvertible or unclassifiable
└── <dropped files>

Week02/materials/
├── .intake-manifest.tsv      # sha256, original name, category, converter, fidelity
├── INTAKE.md                 # human-readable provenance log
├── 01_lecture-notes/
│   ├── lecture3.pdf          # original, preserved
│   └── .converted/
│       └── lecture3.pdf.md   # extracted text Claude reads
├── 02_example-code/
├── 03_in-class-exercises/
└── 04_homework/
```

The original file is always preserved and is the source of truth. The converted
markdown is a reading aid. Both are committed to git.

## Components

### `scripts/set-week.sh WeekXX`

Writes `WeekXX` to `dropper/.active-week`. Validates the `Week[0-9][0-9]` shape.
Creates the week via `new-week.sh` if it does not exist.

### `scripts/intake.sh` — deterministic, no model involvement

Per decision 4 this script is not part of the documented user workflow. It is
the implementation that Claude invokes as step 0 of `do week X`. Running it by
hand is harmless and idempotent, but the supported entry point is `do week X`.

| Stage | Action |
|---|---|
| A | Read `dropper/.active-week`; resolve target week; scaffold it if absent. Abort if the pointer is missing or malformed. |
| B | For each dropped file compute sha256; skip files already in the manifest (idempotent re-runs). |
| C | Convert to markdown; record which converter succeeded and the resulting fidelity grade. |
| D | Apply extension rules to propose a category; write `dropper/_intake-proposal.json`. |
| E | *(model step)* Claude reads each converted file and confirms, corrects, or quarantines the proposal. |
| F | Move original and converted output into the confirmed category folder. |
| G | Append to `.intake-manifest.tsv` and rewrite `INTAKE.md`. |

Stages A–D and F–G are shell. Stage E is the only model step.

### Conversion ladder (stage C)

```text
markitdown <file>
  ├─ non-empty output ──────────→ fidelity CLEAN
  ├─ empty output (scanned PDF) ─→ tesseract OCR ──→ fidelity OCR
  ├─ command failed ─────────────→ pdftotext -layout → fidelity REDUCED
  └─ all failed ─────────────────→ dropper/_unsorted/ → fidelity FAILED
```

Files already in a text format (`.ino`, `.cpp`, `.h`, `.c`, `.md`, `.txt`) skip
conversion entirely and are graded `NATIVE`.

### Extension rules (stage D proposal only)

| Pattern | Proposed category |
|---|---|
| `*.ino`, `*.cpp`, `*.h`, `*.c` | `02_example-code` |
| name matches `hw`, `homework`, `assign` | `04_homework` |
| name matches `lab`, `exercise`, `inclass`, `in-class` | `03_in-class-exercises` |
| anything else | `01_lecture-notes` |

These are proposals only. Except for the code-extension rule, every proposal is
confirmed against converted content before the file is moved.

## Fidelity grades and their consequences

Conversion is lossy. Each grade constrains how its facts may be used:

| Grade | Source | Consequence for generated work |
|---|---|---|
| `NATIVE` | text file read directly | facts usable normally |
| `CLEAN` | markitdown structured output | facts usable normally |
| `REDUCED` | `pdftotext` fallback; layout and tables lost | any pin table, wiring figure, or column-aligned value drawn from it must raise `QUESTIONS.md` |
| `OCR` | tesseract on a scanned page | any GPIO number, resistor value, or timing figure drawn from it must raise `QUESTIONS.md` automatically |
| `FAILED` | unconvertible | file stays in `_unsorted/`; any task depending on it is `NEEDS CLARIFICATION` |

Rationale: an OCR'd "GPIO 16" may actually read "GPIO 18". Presenting it as fact
would violate the repository's rule against inventing hardware mappings.

## `do week X` end-to-end flow

```text
step 0  run intake.sh stages A–D
        Claude confirms classification (stage E), prints the classification table
        stages F–G file the results
step 1  read WeekXX/materials/ (originals plus converted text)
step 2  write WeekXX/generated/INDEX.md
step 3  emit P1, P2, … and HW1, HW2, … each containing
          <ID>.ino, wiring.md, README.md, and QUESTIONS.md when required
step 4  update INDEX.md with per-task completion status
```

The classification table is printed rather than gated, matching decision 4. A
misfile is therefore visible in the transcript even though generation continues.

## Error handling

- Missing or malformed `.active-week`: abort with the `set-week.sh` remedy.
- Empty dropper: report "nothing to intake" and continue to step 1.
- Filename collision in the target category: append `-2`, `-3`; never overwrite.
- Duplicate content (sha256 already in manifest): skip and report as duplicate.
- Any converter failure: quarantine, never silently drop.
- Interrupted run: manifest is append-only and keyed by sha256, so a re-run resumes safely.

## Testing

- `set-week.sh` rejects `Week2`, `week02`, and `Week002`; accepts `Week02`.
- `intake.sh` on an empty dropper exits cleanly.
- A `.ino` dropped in is graded `NATIVE` and lands in `02_example-code`.
- The same file dropped twice is ingested once.
- A file with no text layer routes through the OCR branch and is graded `OCR`.
- A deliberately corrupt PDF lands in `_unsorted/` and is graded `FAILED`.
- A name collision produces `-2` rather than an overwrite.
- Generated `P1/P1.ino` opens in Arduino IDE without a relocation prompt.

## Repository changes required

1. Add `scripts/set-week.sh` and `scripts/intake.sh`.
2. Create `dropper/` with `.active-week` and `_unsorted/.gitkeep`.
3. Amend `CLAUDE.md`: sketch filename becomes `<ID>.ino`; document the dropper,
   the intake step, and the fidelity grades with their consequences.
4. Amend `README.md`: replace the manual filing routine with the dropper routine.
5. Rename `Week01/generated/P1/solution.ino` to `P1.ino` and update references.
6. Amend `.gitignore` so loose dropper files are ignored while `.active-week`,
   `_unsorted/.gitkeep`, and all converted markdown stay tracked.

## Out of scope

- Background file watcher.
- `opendataloader-pdf` as a second engine.
- Automatic compilation or upload (`arduino-cli`); the student compiles and runs.
- Any change to the generation rules themselves beyond the sketch filename.
