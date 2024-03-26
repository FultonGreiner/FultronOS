cc_library(
    name = "fatfs",
    srcs = [
        "source/diskio.c",
        "source/ff.c",
        "source/ffsystem.c",
        "source/ffunicode.c",
        "source/sdram_diskio.c",
    ],
    hdrs = [
        "include/diskio.h",
        "include/ff.h",
        "include/ffconf.h",
        "include/sdram_diskio.h",
    ],
    deps = [
        "//source/drivers/sdram:sdram",
    ],
    includes = ["include"],
    visibility = ["//visibility:public"],
)