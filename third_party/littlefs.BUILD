cc_library(
    name = "littlefs",
    srcs = [
        "lfs_util.c",
        "lfs.c",
    ],
    hdrs = [
        "lfs_util.h",
        "lfs.h",
    ],
    includes = [
        ".",
    ],
    copts = [
        "-DLFS_CONFIG=lfs_config.h",
    ],
    visibility = ["//visibility:public"],
)