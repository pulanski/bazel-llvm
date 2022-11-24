load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "linenoise",
    hdrs = "linenoise.hpp",
    copts = select({
        "@bazel_tools//src/conditions:windows": [],
        "//conditions:default": [
            "-Wno-unused-variable",
            "-Wno-implicit-function-declaration",
        ],
    }),
    visibility = ["//visibility:public"],
)
