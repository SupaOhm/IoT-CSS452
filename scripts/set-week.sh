#!/usr/bin/env bash
# Point the dropper at a week. Everything dropped from now on lands there.
set -euo pipefail

usage() { echo "Usage: $0 WeekXX" >&2; exit 1; }

[[ $# -eq 1 ]] || usage
week="$1"
[[ "$week" =~ ^Week[0-9][0-9]$ ]] || { echo "Week name must look like Week02." >&2; exit 1; }

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
dropper="$root/dropper"
mkdir -p "$dropper/_unsorted"

if [[ ! -d "$root/$week" ]]; then
  echo "$week does not exist yet; creating it."
  "$root/scripts/new-week.sh" "$week"
fi

printf '%s\n' "$week" > "$dropper/.active-week"
echo "Dropper is now pointed at $week."
echo "Drop files into $dropper/ then tell Claude: do $week"
