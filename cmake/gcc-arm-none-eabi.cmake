# Toolchain file for building the DigitalDash Gen2 STM32U5 firmware with the
# Arm GNU bare-metal toolchain (arm-none-eabi-*) instead of STM32CubeIDE.
#
# The compiler is located either from PATH or from ARM_TOOLCHAIN_DIR when set.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

if(DEFINED ENV{ARM_TOOLCHAIN_DIR})
    set(TOOLCHAIN_BIN "$ENV{ARM_TOOLCHAIN_DIR}/")
else()
    set(TOOLCHAIN_BIN "")
endif()

set(CMAKE_C_COMPILER   ${TOOLCHAIN_BIN}${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN}${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN}${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY      ${TOOLCHAIN_BIN}${TOOLCHAIN_PREFIX}objcopy CACHE INTERNAL "")
set(CMAKE_SIZE         ${TOOLCHAIN_BIN}${TOOLCHAIN_PREFIX}size CACHE INTERNAL "")

# Do not try to link a full executable during compiler detection: the firmware
# needs a linker script, which is not available at that stage.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
