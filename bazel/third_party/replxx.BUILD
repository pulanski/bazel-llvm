load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

licenses(["notice"])  # BSD

exports_files(["LICENSE.md"])

cc_binary(
    name = "example_c",
    srcs = [
        "examples/c-api.c",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":examples_util_lib",
    ],
)

cc_binary(
    name = "example_cc",
    srcs = [
        "examples/cxx-api.cxx",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":examples_util_lib",
    ],
)

cc_library(
    name = "examples_util_lib",
    srcs = [
        "examples/util.c",
    ],
    hdrs = [
        "examples/util.h",
    ],
    deps = [
        ":replxx",
    ],
)

cc_library(
    name = "replxx",
    srcs = [
        "src/ConvertUTF.cpp",
        "src/conversion.cxx",
        "src/escape.cxx",
        "src/history.cxx",
        "src/prompt.cxx",
        "src/replxx.cxx",
        "src/replxx_impl.cxx",
        "src/terminal.cxx",
        "src/util.cxx",
        "src/wcwidth.cpp",
        "src/windows.cxx",
    ],
    hdrs = [
        "include/replxx.h",
        "include/replxx.hxx",
        "src/ConvertUTF.h",
        "src/conversion.hxx",
        "src/escape.hxx",
        "src/history.hxx",
        "src/killring.hxx",
        "src/prompt.hxx",
        "src/replxx_impl.hxx",
        "src/terminal.hxx",
        "src/unicodestring.hxx",
        "src/utf8string.hxx",
        "src/util.hxx",
        "src/windows.hxx",
    ],
    includes = [
        "include",
    ],
    linkstatic = True,
    visibility = ["//visibility:public"],
)
