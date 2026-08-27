#!/usr/bin/env bash
# Move the dropper pointer to the next workshop number.
# Run automatically once a workshop's generation is finished.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
dropper="$root/dropper"
pointer="$dropper/.active-workshop"

die() { echo "advance-workshop: $*" >&2; exit 1; }

[[ -f "$pointer" ]] || die "no dropper/.active-workshop. Run ./scripts/set-workshop.sh WorkshopXX"
current="$(tr -d '[:space:]' < "$pointer")"
[[ "$current" =~ ^Workshop[0-9][0-9]$ ]] || die "pointer is malformed ('$current')"

num="${current#Workshop}"
# strip a leading zero so 08/09 are not read as octal
next_num=$((10#$num + 1))
[[ "$next_num" -le 99 ]] || die "$current is the last two-digit workshop; name the next one yourself"
next="$(printf 'Workshop%02d' "$next_num")"

"$root/scripts/set-workshop.sh" "$next" >/dev/null
echo "Dropper advanced: $current -> $next"
echo "Drop the next workshop's files into $dropper/ and say: do $next"
