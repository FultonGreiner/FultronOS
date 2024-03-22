load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "kernel",
    srcs = [
        # "arch/zynq-7000/_start.s",
        # "drivers/uart/uart-zynq.c",
        "kernel/start.c",
        "kernel/syscalls.c",
        "kernel/sysmem.c",
        # "lib/libfc/source/putc.c",
        # "lib/libfc/source/printf.c",
    ],
    deps = [
        "//source/arch/zynq-7000:zynq",
        "//source/drivers/uart:uart",
        "//source/lib/libfc:libfc",
    ],
)
