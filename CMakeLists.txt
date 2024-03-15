cmake_minimum_required(VERSION 3.20)

# ###################### CONSTANTS ######################################

set (PROJECT_TYPE_EXECUTABLE          "exe")
set (MCPU_CORTEX_A8				      "-mcpu=cortex-a8")
set (MFPU_NEON_VFPV3                  "-mfpu=neon-vfpv3")
set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")

set (F_FREESTANDING                   "-ffreestanding") # might be no standard libraries, don't start at 'main', standard functions may not have their usual definitions
set (W_ALL                            "-Wall")
set (W_EXTRA                          "-Wextra")
set (W_ERROR                          "-Werror")
set (STATIC                           "-static")
set (WL_GC_SECTIONS                   "-Wl,--gc-sections")
set (NO_STARTFILES                    "-nostartfiles")
# set (NO_STDLIB                        "-nostdlib")
# set (NO_BUILTIN                       "-fno-builtin")
set (NO_STACK_PROTECTOR               "-fno-stack-protector")
set (M_CPU_CORTEX_A8                  "-mcpu=cortex-a8")
set (M_FPU_NEON_VFPV3                 "-mfpu=neon-vfpv3")
set (M_FLOAT_ABI_SOFTFP               "-mfloat-abi=softfp")
set (M_THUMB                          "-mthumb")
set (WL_LIBS                          "-Wl,--start-group -lc -lm -Wl,--end-group")
set (X_ASSEMBLER_WITH_CPP             "-x assembler-with-cpp")

###################### VARIABLES ######################################
set (PROJECT_NAME             "FultronOS")
set (PROJECT_TYPE             ${PROJECT_TYPE_EXECUTABLE})

set (PROJECT_LINKER_SCRIPT    "-T ${CMAKE_SOURCE_DIR}/kernel/link.ld")
set (GENERATE_MAP_FILE        "-Wl,-Map=${CMAKE_PROJECT_NAME}.map")

set (LINKER_SCRIPT            ${PROJECT_LINKER_SCRIPT})
set (MCPU                     ${MCPU_CORTEX_A8})
set (MFPU                 	  ${M_FPU_NEON_VFPV3})
set (MFLOAT_ABI               ${M_FLOAT_ABI_SOFTFP})
set (RUNTIME_LIBRARY          ${RUNTIME_LIBRARY_REDUCED_C})
set (RUNTIME_LIBRARY_SYSCALLS ${RUNTIME_LIBRARY_SYSCALLS_MINIMAL})

set (PROJECT_SOURCES
    kernel/_start.s 
    kernel/printf.c 
    kernel/putc.c 
    kernel/start.c
    kernel/syscalls.c
    )

set (PROJECT_DEFINES
    )

set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
    include
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

# ${NO_STDLIB} ${NO_BUILTIN}
set (CMAKE_C_FLAGS "${F_FREESTANDING} ${W_ALL} ${W_EXTRA} ${W_ERROR} ${RUNTIME_LIBRARY} ${NO_STARTFILES} ${NO_STACK_PROTECTOR} ${MCPU} ${MFPU} ${MFLOAT_ABI} ${M_THUMB}")
set (CMAKE_EXE_LINKER_FLAGS "${GENERATE_MAP_FILE} ${RUNTIME_LIBRARY_SYSCALLS} ${PROJECT_LINKER_SCRIPT} ${F_FREESTANDING} ${WL_GC_SECTIONS} ${STATIC} ${WL_LIBS}")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} ${X_ASSEMBLER_WITH_CPP}")
