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

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/memmap.ld")
string(APPEND CMAKE_EXE_LINKER_FLAGS " -T${LINKER_SCRIPT}")

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
set_target_properties(${TARGET_NAME} PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})

add_custom_command(TARGET ${FULTRONOS}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS ${FULTRONOS}.elf ${FULTRONOS}.bin -O binary
    )

