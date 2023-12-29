cmake_minimum_required(VERSION 3.6)

project(FultronOS C ASM)

string(TOLOWER ${PROJECT_NAME} FULTRONOS)

list(APPEND CMAKE_C_FLAGS_STRING
    "-Wall"
    "-Wextra"
    "-Werror"
    # "-nostartfiles"
    "-nostdlib"
    "-fno-builtin"
    # "-fno-stack-protector"
    "-mcpu=cortex-a8"
    # "-mfpu=neon-vfpv3"
    # "-mthumb"
    )

list(JOIN CMAKE_C_FLAGS_STRING " " CMAKE_C_FLAGS)

list(APPEND ASM_SOURCES
    kernel/asm/_start.s
    )

list(APPEND C_SOURCES
    kernel/src/gpio.c
    kernel/src/start.c

    lib/libc/stdio/src/printf.c
    lib/libc/stdio/src/putc.c
    )

set_property(SOURCE ${ASM_SOURCES}
    APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp"
    )

add_executable(${FULTRONOS}.elf
    ${ASM_SOURCES}
    ${C_SOURCES}
    )

add_custom_command(TARGET ${FULTRONOS}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS ${FULTRONOS}.elf ${FULTRONOS}.bin -O binary
    )

