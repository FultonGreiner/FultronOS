cmake_minimum_required(VERSION 3.20)

# ###################### CONSTANTS ######################################

set (PROJECT_TYPE_EXECUTABLE          "exe")

set (MARCH_ARMV7A                     "-march=armv7-a")
set (MCPU_CORTEX_A8				      "-mcpu=cortex-a8")
set (MCPU_CORTEX_A9				      "-mcpu=cortex-a9")
set (MCPU_CORTEX_A15				  "-mcpu=cortex-a15")
set (MFPU_NEON_VFPV3                  "-mfpu=neon-vfpv3")
# set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")

# -Wl,--print-memory-usage
set (F_FREESTANDING                   "-ffreestanding") # might be no standard libraries, don't start at 'main', standard functions may not have their usual definitions
set (W_ALL                            "-Wall")
set (W_EXTRA                          "-Wextra")
set (W_ERROR                          "-Werror")
set (STATIC                           "-static")
set (WL_GC_SECTIONS                   "-Wl,--gc-sections")
set (NO_STARTFILES                    "-nostartfiles")
# set (NO_STDLIB                        "-nostdlib") # required for newlib
set (NO_BUILTIN                       "-fno-builtin") # removing causes undefined references to __aeabi_uldivmod
set (NO_STACK_PROTECTOR               "-fno-stack-protector")
set (M_CPU_CORTEX_A8                  "-mcpu=cortex-a8")
set (M_FPU_NEON_VFPV3                 "-mfpu=neon-vfpv3")
set (MFPU_FPV5_SP_D16                 "-mfpu=fpv5-sp-d16")
set (M_FLOAT_ABI_SOFT                 "-mfloat-abi=soft")
set (M_FLOAT_ABI_HARD                 "-mfloat-abi=hard")
set (M_FLOAT_ABI_SOFTFP               "-mfloat-abi=softfp")
set (M_THUMB                          "-mthumb")
set (WL_LIBS                          "-Wl,--start-group -lc -lm -Wl,--end-group")
set (X_ASSEMBLER_WITH_CPP             "-x assembler-with-cpp")

# -ffunction-sections -fdata-sections

###################### VARIABLES ######################################
set (PROJECT_NAME             "FultronOS")
set (PROJECT_TYPE             ${PROJECT_TYPE_EXECUTABLE})

set (PROJECT_LINKER_SCRIPT    "-T ${CMAKE_SOURCE_DIR}/source/kernel/link.ld")
set (GENERATE_MAP_FILE        "-Wl,-Map=${PROJECT_NAME}.map")

set (LINKER_SCRIPT            ${PROJECT_LINKER_SCRIPT})
# set (MARCH                    ${MARCH_ARMV7A})
set (MCPU                     ${MCPU_CORTEX_A15})
# set (MFPU                 	  ${MFPU_FPV5_SP_D16})
# set (MFLOAT_ABI               ${M_FLOAT_ABI_SOFTFP})
set (RUNTIME_LIBRARY          ${RUNTIME_LIBRARY_REDUCED_C})
set (RUNTIME_LIBRARY_SYSCALLS ${RUNTIME_LIBRARY_SYSCALLS_MINIMAL})

set (PROJECT_DIR              ${CMAKE_SOURCE_DIR})
set (SOURCE_DIR               ${PROJECT_DIR}/source)
set (KERNEL_DIR               ${SOURCE_DIR}/kernel)
set (INCLUDE_DIR              ${SOURCE_DIR}/inc)
set (LIB_DIR                  ${SOURCE_DIR}/lib)

set (PROJECT_SOURCES
    ${KERNEL_DIR}/printf.c 
    ${KERNEL_DIR}/putc.c 

    source/drivers/serial/serial.c

    source/arch/i686/entry.s
    source/arch/i686/kernel.c
    )

set (PROJECT_DEFINES
    )

set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
    ${INCLUDE_DIR}
    source/drivers/serial
    )

project(${PROJECT_NAME} ASM C)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
    ARGS ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin -O binary
)

add_compile_definitions (${PROJECT_DEFINES})
include_directories (${PROJECT_INCLUDES})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")

# set (DEBUG_FLAGS                  "-g3 -O0")
set (CMAKE_C_FLAGS_DEBUG          "${DEBUG_FLAGS}")
set (CMAKE_ASM_FLAGS_DEBUG        "${DEBUG_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${DEBUG_FLAGS}")

# i686
set (CMAKE_ASM_FLAGS        "")
set (CMAKE_C_FLAGS          "-ffreestanding -Wall -Wextra")
set (CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/source/arch/i686/link.ld -nostdlib -lgcc")

set (RELEASE_FLAGS                  "-g0 -O3")
set (CMAKE_C_FLAGS_RELEASE          "${RELEASE_FLAGS}")
set (CMAKE_ASM_FLAGS_RELEASE        "${RELEASE_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${RELEASE_FLAGS}")
