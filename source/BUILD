load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "fultronos.elf",
    srcs = [
        "start.c",
        # "test.c",
    ],
    deps = [
        "//source/arch/zynq-7000:zynq",
        "//source/drivers/uart:uart",
        "//source/kernel:kernel",
        "//source/lib/libfc:libfc",
        "//external:xilinx_embeddedsw",

        "@//include:xparameters",
    ],
    copts = [
        # "-Iexternal/xilinx_embeddedsw_lib/lib/bsp/standalone/src/arm/common/gcc",
        # "-Iexternal/xilinx_embeddedsw_lib/lib/bsp/standalone/src/arm/cortexa9",
        # "-Iexternal/xilinx_embeddedsw_lib/lib/bsp/standalone/src/common",
        # "-Iexternal/xilinx_embeddedsw_lib/XilinxProcessorIPLib/drivers/emacps/src",
        # "-Iexternal/xilinx_embeddedsw_lib/XilinxProcessorIPLib/drivers/uartlite/src",
        # "-Iexternal/xilinx_embeddedsw_lib/XilinxProcessorIPLib/drivers/common/src",
    ],
)
