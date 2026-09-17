#!/usr/bin/env bash
#
# Generate fallback LVGL fonts for the custom "Discongnate_NN" typefaces that
# the UI code references (declared in lv_conf.h via LV_FONT_CUSTOM_DECLARE) but
# whose source files are not committed to this repository.
#
# These placeholders are generated from a substitute TTF (DejaVu Sans by
# default) so the firmware can be compiled and linked headlessly / in CI. They
# are NOT the original artwork typeface -- if the real Discongnate_*.c font
# files are added to the repo, this script becomes a no-op.
#
# Requires: node/npx (for lv_font_conv) and a TTF file.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT_DIR="${REPO_ROOT}/ui/generated_fonts"

# Font point sizes referenced by the UI / declared in lv_conf.h.
SIZES=(14 18 22 24 30 32 38 48 52)

# If the real (committed) font sources are present anywhere under ui/, do nothing.
if grep -rlq "const lv_font_t Discongnate_18" "${REPO_ROOT}/ui" 2>/dev/null; then
    if [ ! -d "${OUT_DIR}" ] || ! grep -rlq "generated fallback" "${OUT_DIR}" 2>/dev/null; then
        echo "[fonts] Real Discongnate font sources found -- skipping fallback generation."
        exit 0
    fi
fi

# Locate a TTF to use as the substitute typeface.
TTF="${DISCONGNATE_FALLBACK_TTF:-}"
if [ -z "${TTF}" ]; then
    for candidate in \
        /usr/share/fonts/truetype/dejavu/DejaVuSans.ttf \
        /usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf \
        /usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf; do
        if [ -f "${candidate}" ]; then
            TTF="${candidate}"
            break
        fi
    done
fi

if [ -z "${TTF}" ] || [ ! -f "${TTF}" ]; then
    echo "[fonts] ERROR: no substitute TTF found. Install fonts-dejavu-core or set DISCONGNATE_FALLBACK_TTF." >&2
    exit 1
fi

# Skip regeneration if all target files already exist (keeps rebuilds fast).
all_present=1
for size in "${SIZES[@]}"; do
    [ -f "${OUT_DIR}/Discongnate_${size}.c" ] || all_present=0
done
if [ "${all_present}" -eq 1 ]; then
    echo "[fonts] Fallback fonts already present -- skipping generation."
    exit 0
fi

mkdir -p "${OUT_DIR}"
echo "[fonts] Generating fallback Discongnate fonts from ${TTF} into ${OUT_DIR}"

for size in "${SIZES[@]}"; do
    out="${OUT_DIR}/Discongnate_${size}.c"
    npx --yes lv_font_conv@latest \
        --font "${TTF}" \
        --size "${size}" \
        --bpp 4 \
        --format lvgl \
        --lv-include lvgl.h \
        -r 0x20-0x7F \
        -o "${out}" >/dev/null 2>&1
    # Tag the file so the skip-check above can detect these as generated.
    sed -i '1s;^;/* generated fallback font -- see scripts/gen_fallback_fonts.sh */\n;' "${out}"
    echo "[fonts]   Discongnate_${size}.c"
done

echo "[fonts] Done."
