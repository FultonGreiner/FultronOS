cmake_minimum_required(VERSION 3.20)

# ###################### CONSTANTS ######################################

set (PROJECT_TYPE_EXECUTABLE          "exe")

set (MARCH_ARMV7A                     "-march=armv7-a")
set (MCPU_CORTEX_A9				      "-mcpu=cortex-a9")
set (MFPU_VFPV3                       "-mfpu=vfpv3")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")

# -Wl,--print-memory-usage
set (FFREESTANDING                    "-ffreestanding") # might be no standard libraries, don't start at 'main', standard functions may not have their usual definitions
# set (W_ALL                            "-Wall")
# set (W_EXTRA                          "-Wextra")
# set (W_ERROR                          "-Werror")
# set (STATIC                           "-static")
# set (WL_GC_SECTIONS                   "-Wl,--gc-sections")
set (NO_BUILTIN                       "-fno-builtin") # removing causes undefined references to __aeabi_uldivmod
set (NO_STARTFILES                    "-nostartfiles")
set (NO_STDLIB                        "-nostdlib") # required for newlib
set (WL_LIBS                          "-Wl,--start-group -lc -lm -Wl,--end-group")

set (MLITTLE_ENDIAN                   "-mlittle-endian")

# set (NO_STACK_PROTECTOR               "-fno-stack-protector")
# -ffunction-sections -fdata-sections

###################### VARIABLES ######################################
set (PROJECT_NAME             "FultronOS")
set (PROJECT_TYPE             ${PROJECT_TYPE_EXECUTABLE})

set (PROJECT_LINKER_SCRIPT    "-T ${CMAKE_SOURCE_DIR}/source/arch/zynq-7000/link.ld")
set (GENERATE_MAP_FILE        "-Wl,-Map=${PROJECT_NAME}.map")

set (LINKER_SCRIPT            ${PROJECT_LINKER_SCRIPT})

set (MARCH                    ${MARCH_ARMV7A})
set (MCPU                     ${MCPU_CORTEX_A9})
set (MENDIAN                  ${MLITTLE_ENDIAN})
set (MFLOAT_ABI               ${M_FLOAT_ABI_HARD})
set (MFPU                 	  ${MFPU_VFPV3})
set (RUNTIME_LIBRARY          ${RUNTIME_LIBRARY_REDUCED_C})
set (RUNTIME_LIBRARY_SYSCALLS ${RUNTIME_LIBRARY_SYSCALLS_MINIMAL})

set (PROJECT_DIR              ${CMAKE_SOURCE_DIR})
set (SOURCE_DIR               ${PROJECT_DIR}/source)
set (KERNEL_DIR               ${SOURCE_DIR}/kernel)
set (INCLUDE_DIR              ${SOURCE_DIR}/inc)
set (LIB_DIR                  ${SOURCE_DIR}/lib)

# -nostartfiles -nostdlib -fno-builtin -mthumb

set (PROJECT_SOURCES
    source/arch/zynq-7000/_start.s
    source/drivers/device/device.c
    source/drivers/uart/uart-zynq.c
    source/kernel/start.c
    source/kernel/syscalls.c
    source/kernel/sysmem.c
    source/lib/libfc/source/putc.c
    source/lib/libfc/source/printf.c
    )

set (PROJECT_DEFINES
    )

set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
    source/drivers/device
    source/drivers/uart
    source/lib/libfc
    source/lib/libfc/include
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

set (DEBUG_FLAGS                  "-g3 -O0")
set (CMAKE_C_FLAGS_DEBUG          ${DEBUG_FLAGS})
set (CMAKE_ASM_FLAGS_DEBUG        ${DEBUG_FLAGS})

set (RELEASE_FLAGS                  "-g0 -O3")
set (CMAKE_C_FLAGS_RELEASE          ${RELEASE_FLAGS})
set (CMAKE_ASM_FLAGS_RELEASE        ${RELEASE_FLAGS})

string (JOIN " " CMAKE_ASM_FLAGS
    ${FFREESTANDING}
    ${MARCH}
    ${MCPU}
    ${MENDIAN}
    ${MFLOAT_ABI}
    ${MFPU}
    ${NO_STARTFILES}
    ${NO_STDLIB}
    # ${NO_BUILTIN}
    # ${XASSEMBLER_WITH_CPP}
)

string (JOIN " " CMAKE_C_FLAGS
    ${FFREESTANDING}
    ${MARCH}
    ${MCPU}
    ${MENDIAN}
    ${MFLOAT_ABI}
    ${MFPU}
    ${NO_STARTFILES}
    # ${NO_STDLIB}
    ${NO_BUILTIN}
    # "-lgcc"
    # "-mthumb"
    ${WL_LIBS}
)

string (JOIN " " CMAKE_EXE_LINKER_FLAGS
    ${GENERATE_MAP_FILE} 
    # ${NO_STDLIB}
    ${PROJECT_LINKER_SCRIPT}
    ${NO_BUILTIN}
    ${RUNTIME_LIBRARY_SYSCALLS}
    # "-lgcc"
    # "-mthumb"
    ${WL_LIBS}
)
