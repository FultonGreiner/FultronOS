load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

new_git_repository(
    name = "xilinx_embeddedsw_lib",
    remote = "https://github.com/Xilinx/embeddedsw.git",
    tag = "xilinx-v2020.3",
    build_file = "//third_party:xilinx_embeddedsw.BUILD",
)

bind(
    name = "xilinx_embeddedsw",
    actual = "@xilinx_embeddedsw_lib//:xilinx_embeddedsw",
)

new_git_repository(
    name = "littlefs_lib",
    remote = "https://github.com/littlefs-project/littlefs.git",
    tag = "v2.9.1",
    build_file = "//third_party:littlefs.BUILD",
)

bind(
    name = "littlefs",
    actual = "@littlefs_lib//:littlefs",
)

register_toolchains(
    "//bazel/toolchain:arm_none_eabi_gcc_darwin_arm64",
)