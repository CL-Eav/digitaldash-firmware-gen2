# Headless CMake build for the DigitalDash Gen2 STM32U5 firmware.
#
# This mirrors the STM32CubeIDE "Debug" managed build (sources, include paths,
# defines, CPU flags and linker settings extracted from the .cproject) so the
# firmware can be compiled from the command line / CI without the IDE.
#
# Usage:
#   cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
#   cmake --build build
#
# Requires the git submodules (lvgl + KE libs) to be initialised and
# build_info.h to be generated (scripts/gen_build_info.py).

cmake_minimum_required(VERSION 3.20)

project(digitaldash-firmware-gen2 C ASM)

set(TARGET digitaldash-firmware-gen2-stm32u5g)

# ---------------------------------------------------------------------------
# CPU / architecture
# ---------------------------------------------------------------------------
set(CPU_FLAGS
    -mcpu=cortex-m33
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard
    -mthumb)

# ---------------------------------------------------------------------------
# Preprocessor defines (from .cproject Debug configuration)
# ---------------------------------------------------------------------------
set(FW_DEFINES
    USE_HAL_DRIVER
    STM32U5G9xx
    USE_KE_CONF
    ENABLE_WHEN_ENGINE_ON=1
    FORD_FOCUS_STRS_2013_2018
    DEBUG)

# ---------------------------------------------------------------------------
# Include paths (from .cproject)
# ---------------------------------------------------------------------------
set(FW_INCLUDES
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/STM32U5xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/STM32U5xx_HAL_Driver/Inc/Legacy
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32U5xx/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/lib/lib_can_bus_sniffer/inc
    ${CMAKE_SOURCE_DIR}/lib/lib_digitaldash_config/inc
    ${CMAKE_SOURCE_DIR}/lib/lib_digital_dash/inc
    ${CMAKE_SOURCE_DIR}/lib/lib_ke_protocol/inc
    ${CMAKE_SOURCE_DIR}/lib/lib_obdii/inc
    ${CMAKE_SOURCE_DIR}/lib/lib_pid/src
    ${CMAKE_SOURCE_DIR}/lib/lib_unit_conversion/inc
    ${CMAKE_SOURCE_DIR}/lib/lib_vehicle_data/inc
    ${CMAKE_SOURCE_DIR}/lvgl
    ${CMAKE_SOURCE_DIR}/lvgl/libs/nema_gfx/include
    ${CMAKE_SOURCE_DIR}/ui)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/Core/Src/*.c)

set(STARTUP_SOURCE ${CMAKE_SOURCE_DIR}/Core/Startup/startup_stm32u5g9zjtxq.s)

file(GLOB HAL_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/Drivers/STM32U5xx_HAL_Driver/Src/*.c)
# HAL ships *_template.c helpers that must not be compiled into the app.
list(FILTER HAL_SOURCES EXCLUDE REGEX ".*_template\\.c$")

file(GLOB_RECURSE UI_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/ui/*.c)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/lib/*/src/*.c)

# LVGL: compile the whole tree except the unit-test harness (matches the
# STM32CubeIDE source folder configuration).
file(GLOB_RECURSE LVGL_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/lvgl/*.c)
list(FILTER LVGL_SOURCES EXCLUDE REGEX "/lvgl/tests/")

add_executable(${TARGET}
    ${CORE_SOURCES}
    ${STARTUP_SOURCE}
    ${HAL_SOURCES}
    ${UI_SOURCES}
    ${LIB_SOURCES}
    ${LVGL_SOURCES})

target_include_directories(${TARGET} PRIVATE ${FW_INCLUDES})
target_compile_definitions(${TARGET} PRIVATE ${FW_DEFINES})

target_compile_options(${TARGET} PRIVATE
    ${CPU_FLAGS}
    $<$<COMPILE_LANGUAGE:C>:-std=gnu11>
    -Og
    -g3
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wa,--noexecstack)

# ---------------------------------------------------------------------------
# Link
# ---------------------------------------------------------------------------
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32U5G9ZJTXQ_FLASH.ld)
set(NEMA_LIB_DIR ${CMAKE_SOURCE_DIR}/lvgl/libs/nema_gfx/lib/core/cortex_m33_revC/gcc)

target_link_options(${TARGET} PRIVATE
    ${CPU_FLAGS}
    -T${LINKER_SCRIPT}
    --specs=nano.specs
    -u_printf_float
    -Wl,--gc-sections
    -Wl,-Map=${TARGET}.map
    -Wl,--start-group -lc -lm -Wl,--end-group
    -L${NEMA_LIB_DIR})

target_link_libraries(${TARGET} PRIVATE nemagfx-float-abi-hard)

set_target_properties(${TARGET} PROPERTIES
    SUFFIX .elf
    LINK_DEPENDS ${LINKER_SCRIPT})

# ---------------------------------------------------------------------------
# Post-build: size + raw binary
# ---------------------------------------------------------------------------
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${TARGET}>
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET}> ${TARGET}.bin
    COMMENT "Firmware size and raw binary")
