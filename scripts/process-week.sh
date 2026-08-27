#!/usr/bin/env bash
set -euo pipefail

usage() {
  echo "Usage: $0 WeekXX [--dry-run]" >&2
  exit 1
}

[[ $# -ge 1 && $# -le 2 ]] || usage
week="$1"
dry_run="${2:-}"
[[ "$week" =~ ^Week[0-9][0-9]$ ]] || { echo "Week name must look like Week02." >&2; exit 1; }
[[ -z "$dry_run" || "$dry_run" == "--dry-run" ]] || usage

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
week_path="$root/$week"
[[ -d "$week_path/materials" ]] || { echo "Missing: $week_path/materials. Create it with ./scripts/new-week.sh $week" >&2; exit 1; }

required=(01_lecture-notes 02_example-code 03_in-class-exercises 04_homework)
for folder in "${required[@]}"; do
  [[ -d "$week_path/materials/$folder" ]] || { echo "Missing category: materials/$folder" >&2; exit 1; }
done

mkdir -p "$week_path/generated"

prompt="Process $week according to CLAUDE.md.

Read every file under $week/materials/ before producing output. Treat the supplied material as the source of truth. Identify each in-class exercise and homework task, write generated/INDEX.md, and create P1/P2/... plus HW1/HW2/... folders as required.

For every task create solution.ino, wiring.md, and README.md. If any required fact is missing, ambiguous, conflicting, or unreadable, create QUESTIONS.md and mark the task NEEDS CLARIFICATION. Never guess GPIO pins, wiring, values, libraries, timing, or requirements. Preserve the course's terminology and code style."

if [[ "$dry_run" == "--dry-run" ]]; then
  printf '%s\n' "$prompt"
  exit 0
fi

cd "$root"
command -v claude >/dev/null 2>&1 || { echo "Claude Code CLI ('claude') was not found in your terminal." >&2; exit 1; }
claude "$prompt"
