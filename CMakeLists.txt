cmake_minimum_required(VERSION 3.20)

# ###################### CONSTANTS ######################################
set (PROJECT_TYPE_EXECUTABLE          "exe")
set (PROJECT_LINKER_SCRIPT             "../memmap.ld")
set (MCPU_CORTEX_A8				      "-mcpu=cortex-a8")
# set (MFPU_FPV4_SP_D16                 "-mfpu=fpv4-sp-d16")
# set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
set (MFPU_NEON_VFPV3                  "-mfpu=neon-vfpv3")
set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")

#######################################################################
# CCFLAGS ?= -ffreestanding -Wall -Wextra -Werror -nostartfiles -nostdlib -fno-builtin -fno-stack-protector -mcpu=cortex-a8 -mfpu=neon-vfpv3 -mfloat-abi=softfp -mthumb 
# CCFLAGS += -nostdlib
###################### VARIABLES ######################################
set (PROJECT_NAME             "FultronOS")
string(TOLOWER ${PROJECT_NAME} FULTRONOS)
set (PROJECT_TYPE             ${PROJECT_TYPE_EXECUTABLE})
set (LINKER_SCRIPT            ${PROJECT_LINKER_SCRIPT})
set (MCPU                     ${MCPU_CORTEX_A8})
set (MFPU                 	  ${MFPU_NEON_VFPV3})
set (MFLOAT_ABI               ${MFLOAT_ABI_MIX})
# set (RUNTIME_LIBRARY          ${RUNTIME_LIBRARY_REDUCED_C})
# set (RUNTIME_LIBRARY_SYSCALLS ${RUNTIME_LIBRARY_SYSCALLS_MINIMAL})

set (PROJECT_SOURCES
    kernel/_start.s 
    kernel/printf.c 
    kernel/putc.c 
    kernel/start.c
    )

set (PROJECT_DEFINES
    )

set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
    include
    # lib/libc/stdio/inc
    )

project(${PROJECT_NAME} ASM C)
# enable_language(ASM)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    )

add_compile_definitions (${PROJECT_DEFINES})
include_directories (${PROJECT_INCLUDES})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_C_FLAGS "-ffreestanding -Wall -Wextra -Werror -nostartfiles -nostdlib -fno-builtin -fno-stack-protector -mcpu=cortex-a8 -mfpu=neon-vfpv3 -mfloat-abi=softfp -mthumb")
set (CMAKE_EXE_LINKER_FLAGS "-T ../kernel/link.ld -ffreestanding -lgcc -lm -lg")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

################################################################################

# project(FultronOS C ASM)

# string(TOLOWER ${PROJECT_NAME} FULTRONOS)

# list(APPEND CMAKE_C_FLAGS_STRING
#     "-Wall"
#     "-Wextra"
#     "-Werror"
#     # "-nostartfiles"
#     "-nostdlib"
#     "-fno-builtin"
#     # "-fno-stack-protector"
#     "-mcpu=cortex-a8"
#     "-mfpu=neon-vfpv3"
#     # "-mfloat-abi=softfp"
#     # "-mthumb"
#     )

# # list(JOIN CMAKE_C_FLAGS_STRING " " CMAKE_C_FLAGS)
# # set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-mcpu=cortex-a8 -mfpu=neon -ftree-vectorize -ffast-math -mfloat-abi=softfp") # -nostartfiles -nostdlib
# set(CMAKE_C_FLAGS "-Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a8 -mno-unaligned-access -marm -fno-builtin -fno-stack-protector")

# set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/memmap.ld -lm")
# string(APPEND CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT}")

# list(APPEND ASM_SOURCES
#     kernel/asm/_start.s
#     )

# list(APPEND C_SOURCES
#     kernel/src/gpio.c
#     kernel/src/start.c
#     kernel/src/syscalls.c
#     kernel/src/sysmem.c

#     lib/libc/stdio/src/printf.c
#     lib/libc/stdio/src/putc.c
#     )

# set_property(SOURCE ${ASM_SOURCES}
#     APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp"
#     )

# add_executable(${FULTRONOS}.elf
#     ${ASM_SOURCES}
#     ${C_SOURCES}
#     )
# set_target_properties(${TARGET_NAME} PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})

# add_custom_command(TARGET ${FULTRONOS}.elf POST_BUILD
#     COMMAND ${CMAKE_OBJCOPY} ARGS ${FULTRONOS}.elf ${FULTRONOS}.bin -O binary
#     )
