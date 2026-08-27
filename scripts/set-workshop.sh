#!/usr/bin/env bash
# Point the dropper at a workshop. Everything dropped from now on lands there.
set -euo pipefail

usage() { echo "Usage: $0 WorkshopXX" >&2; exit 1; }

[[ $# -eq 1 ]] || usage
workshop="$1"
[[ "$workshop" =~ ^Workshop[0-9][0-9]$ ]] || { echo "Workshop name must look like Workshop02." >&2; exit 1; }

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
dropper="$root/dropper"
mkdir -p "$dropper/_unsorted"

if [[ ! -d "$root/$workshop" ]]; then
  echo "$workshop does not exist yet; creating it."
  "$root/scripts/new-workshop.sh" "$workshop"
fi

printf '%s\n' "$workshop" > "$dropper/.active-workshop"
echo "Dropper is now pointed at $workshop."
echo "Drop files into $dropper/ then tell Claude: do $workshop"
