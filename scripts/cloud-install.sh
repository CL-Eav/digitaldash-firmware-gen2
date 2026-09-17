#!/usr/bin/env bash
#
# Cloud Agent bootstrap for the DigitalDash Gen2 STM32U5 firmware.
#
# Prepares everything needed to build the firmware headlessly (without
# STM32CubeIDE) and performs a build to verify the environment. Safe to run
# repeatedly: every step is guarded / idempotent.
#
#   1. Ensure the Arm GNU bare-metal toolchain + build tools are installed.
#   2. Initialise git submodules (LVGL + Kaiser Engineering libraries).
#   3. Generate build_info.h and fallback fonts.
#   4. Configure and build the firmware with CMake + Ninja.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "${REPO_ROOT}"

ARM_TOOLCHAIN_URL="https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi.tar.xz"
ARM_TOOLCHAIN_DIR="/opt/arm-gnu-toolchain"

echo "==> [1/4] Ensuring toolchain and build tools"

# System packages (ninja, cmake, python, a substitute TTF for fallback fonts).
NEED_APT=()
command -v ninja  >/dev/null 2>&1 || NEED_APT+=(ninja-build)
command -v cmake  >/dev/null 2>&1 || NEED_APT+=(cmake)
command -v python3 >/dev/null 2>&1 || NEED_APT+=(python3)
[ -f /usr/share/fonts/truetype/dejavu/DejaVuSans.ttf ] || NEED_APT+=(fonts-dejavu-core)
if [ "${#NEED_APT[@]}" -gt 0 ]; then
    echo "    Installing: ${NEED_APT[*]}"
    sudo apt-get update -qq
    sudo DEBIAN_FRONTEND=noninteractive apt-get install -y -qq "${NEED_APT[@]}"
fi

# Arm GNU toolchain (arm-none-eabi-*).
if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    if [ ! -x "${ARM_TOOLCHAIN_DIR}/bin/arm-none-eabi-gcc" ]; then
        echo "    Downloading Arm GNU toolchain"
        tmp_tar="$(mktemp --suffix=.tar.xz)"
        curl -fL --retry 3 -o "${tmp_tar}" "${ARM_TOOLCHAIN_URL}"
        sudo mkdir -p "${ARM_TOOLCHAIN_DIR}"
        sudo tar -xf "${tmp_tar}" -C "${ARM_TOOLCHAIN_DIR}" --strip-components=1
        rm -f "${tmp_tar}"
    fi
    sudo ln -sf "${ARM_TOOLCHAIN_DIR}"/bin/arm-none-eabi-* /usr/local/bin/
fi
arm-none-eabi-gcc --version | head -1

echo "==> [2/4] Initialising git submodules"
git submodule update --init --recursive

echo "==> [3/4] Generating build_info.h and fonts"
python3 scripts/gen_build_info.py
bash scripts/gen_fallback_fonts.sh

echo "==> [4/4] Configuring and building firmware"
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
cmake --build build

echo ""
echo "==> Build complete:"
ls -la build/*.elf build/*.bin
