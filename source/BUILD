load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "fultronos.elf",
    srcs = [
        "start.c",
    ],
    deps = [
        "//source/arch/zynq-7000:zynq",
        "//source/drivers/uartps:uartps",
        "//source/kernel:kernel",
        "//source/lib/libfc:libfc",
        
        "//source/system/fatfs:fatfs",
    ],
    copts = [
    ],
)
