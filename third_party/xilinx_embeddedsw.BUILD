cc_library(
    name = "xdrivers",
    srcs = [
        "lib/bsp/standalone/src/common/xil_assert.c",
        "lib/bsp/standalone/src/common/xplatform_info.c",

        "XilinxProcessorIPLib/drivers/emacps/src/xemacps.c",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_bdring.c",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_control.c",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_g.c",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_hw.c",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_intr.c",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_sinit.c",

        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite_g.c",
        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite_intr.c",
        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite_l.c",
        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite_selftest.c",
        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite_sinit.c",
        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite_stats.c",
        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite.c",

        "XilinxProcessorIPLib/drivers/uartps/src/xuartps_g.c",
        "XilinxProcessorIPLib/drivers/uartps/src/xuartps_hw.c",
        "XilinxProcessorIPLib/drivers/uartps/src/xuartps_intr.c",
        "XilinxProcessorIPLib/drivers/uartps/src/xuartps_options.c",
        "XilinxProcessorIPLib/drivers/uartps/src/xuartps_selftest.c",
        "XilinxProcessorIPLib/drivers/uartps/src/xuartps_sinit.c",
        "XilinxProcessorIPLib/drivers/uartps/src/xuartps.c",
    ],
    hdrs = [
        "lib/bsp/standalone/src/arm/common/gcc/xpseudo_asm_gcc.h",

        "lib/bsp/standalone/src/arm/cortexa9/xil_cache_l.h",
        "lib/bsp/standalone/src/arm/cortexa9/xil_cache.h",
        "lib/bsp/standalone/src/arm/cortexa9/xpseudo_asm.h",
        "lib/bsp/standalone/src/arm/cortexa9/xreg_cortexa9.h",

        "lib/bsp/standalone/src/common/xil_assert.h",
        "lib/bsp/standalone/src/common/xplatform_info.h",
        "lib/bsp/standalone/src/common/xil_io.h",
        "lib/bsp/standalone/src/common/xil_printf.h",
        "lib/bsp/standalone/src/common/xil_types.h",
        "lib/bsp/standalone/src/common/xstatus.h",

        # "XilinxProcessorIPLib/drivers/common/src/xparameters.h",

        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_bd.h",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_bdring.h",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps_hw.h",
        "XilinxProcessorIPLib/drivers/emacps/src/xemacps.h",

        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite_i.h",
        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite_l.h",
        # "XilinxProcessorIPLib/drivers/uartlite/src/xuartlite.h",

        "XilinxProcessorIPLib/drivers/uartps/src/xuartps_hw.h",
        "XilinxProcessorIPLib/drivers/uartps/src/xuartps.h",
    ],
    copts = [
        "-Iexternal/xilinx_embeddedsw_lib/lib/bsp/standalone/src/arm/common/gcc",
        "-Iexternal/xilinx_embeddedsw_lib/lib/bsp/standalone/src/arm/cortexa9",
        "-Iexternal/xilinx_embeddedsw_lib/lib/bsp/standalone/src/common",
        "-Iexternal/xilinx_embeddedsw_lib/XilinxProcessorIPLib/drivers/emacps/src",
        # "-Iexternal/xilinx_embeddedsw_lib/XilinxProcessorIPLib/drivers/uartlite/src",
        "-Iexternal/xilinx_embeddedsw_lib/XilinxProcessorIPLib/drivers/uartps/src",
        "-Iexternal/xilinx_embeddedsw_lib/XilinxProcessorIPLib/drivers/common/src",
    ],
    deps = [
        "@//include:xbspconfig",
        "@//include:xparameters",
    ],
)

cc_library(
    name = "xilinx_embeddedsw",
    srcs = [
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":xdrivers",
    ],
)
