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
[[ -d "$workshop_path/materials" ]] || { echo "Missing: $workshop_path/materials. Create it with ./scripts/new-workshop.sh $workshop" >&2; exit 1; }

required=(01_lecture-notes 02_example-code 03_in-class-exercises 04_homework)
for folder in "${required[@]}"; do
  [[ -d "$workshop_path/materials/$folder" ]] || { echo "Missing category: materials/$folder" >&2; exit 1; }
done

mkdir -p "$workshop_path/generated"

prompt="Process $workshop according to CLAUDE.md.

Step 0: run ./scripts/intake.sh scan, confirm each proposed category against the
converted text, then ./scripts/intake.sh apply. Print the classification table.

Then read every file under $workshop/materials/ before producing output. Treat the
supplied material as the source of truth. Identify each in-class exercise and homework
task, write generated/INDEX.md, and create Exercise1/Exercise2/... for in-class tasks plus
P1/P2/P3 (the instructor's video names) for homework tasks, as required.

For every task create <ID>/<ID>.ino (the sketch in its own subfolder, e.g. P1/P1/P1.ino),
plus wiring.md and README.md one level above it, in the task folder itself.
If any required fact is missing, ambiguous, conflicting, or unreadable, create
QUESTIONS.md and mark the task NEEDS CLARIFICATION. Never guess GPIO pins, wiring, values,
libraries, timing, or requirements. Preserve the course's terminology and code style."

if [[ "$dry_run" == "--dry-run" ]]; then
  printf '%s\n' "$prompt"
  exit 0
fi

cd "$root"
command -v claude >/dev/null 2>&1 || { echo "Claude Code CLI ('claude') was not found in your terminal." >&2; exit 1; }
claude "$prompt"
