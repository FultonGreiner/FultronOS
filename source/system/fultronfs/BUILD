cc_library(
    name = "fultronfs",
    srcs = [
        "source/disk.c",
        "source/fultronfs.c",
    ],
    hdrs = [
        "include/disk.h",
        "include/fultronfs_config.h",
        "include/fultronfs.h",
        "include/super_block.h",
    ],
    includes = [
        "include",
    ],
    copts = [
    ],
    deps = [
        "//source/lib/libfc:libfc",
        "//source/drivers/sdram:sdram",
    ],
    visibility = ["//visibility:public"],
)