cc_library(
    name = "littlefs",
    srcs = [
        "source/lfs_util.c",
        "source/lfs.c",
    ],
    hdrs = [
        "include/lfs_config.h",
        "include/lfs_util.h",
        "include/lfs.h",
    ],
    includes = [
        "include",
    ],
    copts = [
        "-DLFS_CONFIG=source/system/littlefs/include/lfs_config.h",
    ],
    visibility = ["//visibility:public"],
)