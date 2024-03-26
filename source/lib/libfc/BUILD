cc_library(
    name = "libfc",
    srcs = [
        "source/printf.c",
        "source/putc.c",
    ],
    hdrs = [
        "include/printf.h",
    ],
    includes = [
        "include",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//source/drivers/uartps:uartps",
    ],
)