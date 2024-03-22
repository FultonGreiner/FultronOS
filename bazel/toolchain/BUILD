load("@bazel_tools//tools/cpp:unix_cc_toolchain_config.bzl", "cc_toolchain_config")

filegroup(
    name = "all",
    srcs = glob([
        "**/*",
    ]),
)

cc_toolchain(
    name = "cc_toolchain",
    all_files = ":all",
    ar_files = ":all",
    as_files = ":all",
    compiler_files = ":all",
    dwp_files = ":all",
    linker_files = ":all",
    objcopy_files = ":all",
    strip_files = ":all",
    static_runtime_lib = ":all",
    toolchain_config = ":my_cc_toolchain_config",
)

cc_toolchain_config(
    name = "my_cc_toolchain_config",
    cpu = "arm64",
    compiler = "gcc",
    toolchain_identifier = "arm64_gcc",
    host_system_name = "local",
    target_system_name = "local",
    target_libc = "unknown",
    abi_version = "unknown",
    abi_libc_version = "unknown",
    tool_paths = {
        "gcc":      "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-gcc",
        "cpp":      "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-g++",
        "ar":       "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-ar",
        "nm":       "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-nm",
        "ld":       "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-ld",
        "as":       "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-as",
        "objcopy":  "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-objcopy",
        "objdump":  "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-objdump",
        "gcov":     "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-gcov",
        "strip":    "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-strip",
        "llvm-cov": "/bin/false",
        # "llvm-cov": "/opt/homebrew/bin/cargo-llvm-cov",
    },
    compile_flags = [
        "--specs=nosys.specs",
        "-ffreestanding",
        "-fno-builtin",
        "-march=armv7-a",
        "-mcpu=cortex-a9",
        "-mfloat-abi=hard",
        "-mfpu=vfpv3",
        "-mlittle-endian",
        "-nostartfiles",
        "-nostdlib",
        "-Wl,--start-group -lc -lm -Wl,--end-group",
    ],
    cxx_builtin_include_directories = [ # NEW
        "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/lib/gcc/arm-none-eabi/13.2.1/include",
        "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/arm-none-eabi/include",
    ],
    link_flags = [
        "--specs=nosys.specs",
        "-fno-builtin",
        "-march=armv7-a",
        "-mcpu=cortex-a9",
        "-mfloat-abi=hard",
        "-mfpu=vfpv3",
        "-nostartfiles",
        "-T /Users/fultongreiner/Development/FultronOS/source/arch/zynq-7000/link.ld",
        "-Wl,--start-group -lc -lm -Wl,--end-group",
    ],
)

toolchain(
    name = "arm64_gcc_linux_x86_64",
    exec_compatible_with = [
        "@platforms//os:osx",
        "@platforms//cpu:aarch64",
    ],
    target_compatible_with = [
        "@platforms//cpu:arm64",
    ],
    toolchain_type = "@rules_cc//cc:toolchain_type",
    toolchain = ":cc_toolchain",
)
