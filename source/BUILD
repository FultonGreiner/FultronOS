load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "fultronos.elf",
    srcs = [
        "start.c",
        # "kernel/syscalls.c",
        # "kernel/sysmem.c",
    ],
    deps = [
        "//source/arch/zynq-7000:zynq",
        "//source/drivers/uart:uart",
        "//source/kernel:kernel",
        "//source/lib/libfc:libfc",
    ],
)
