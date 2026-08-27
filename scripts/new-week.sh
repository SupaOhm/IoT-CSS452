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
folders=(
  "materials/01_lecture-notes"
  "materials/02_example-code"
  "materials/03_in-class-exercises"
  "materials/04_homework"
  "generated"
)

if [[ -d "$week_path" ]]; then
  echo "Refusing to overwrite existing folder: $week_path" >&2
  exit 1
fi

if [[ "$dry_run" == "--dry-run" ]]; then
  printf 'Would create: %s\n' "$week_path"
  printf '  %s\n' "${folders[@]}"
  exit 0
fi

for folder in "${folders[@]}"; do
  mkdir -p "$week_path/$folder"
done

touch "$week_path/materials/01_lecture-notes/.gitkeep"
touch "$week_path/materials/02_example-code/.gitkeep"
touch "$week_path/materials/03_in-class-exercises/.gitkeep"
touch "$week_path/materials/04_homework/.gitkeep"
touch "$week_path/generated/.gitkeep"
echo "Created $week. Add your course files under $week_path/materials/, then run ./scripts/process-week.sh $week"
