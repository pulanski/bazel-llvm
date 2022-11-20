"""Transitive dependencies for llvm."""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

ZSTD_SHA = "188ba167e7a507b545c5f455af4afe3a34b2cee5551949fa000a8218ff4fda67"
ZSTD_VERSION = "bd2740f3476c46b9f69d59e49e7391c2762e04b3"

def llvm_transitive_deps():
    """Fetches transitive dependencies (zlib and zstd, used for compression in optimization passes) of LLVM for header generation."""

    # Configure zstd, a real-time compression library for C/C++
    # See https://github.com/facebook/zstd for more details.
    maybe(
        http_archive,
        name = "com_facebook_zstd",
        build_file = "@com_pulanski_bazel_llvm//:third_party/zstd.BUILD",
        sha256 = ZSTD_SHA,
        strip_prefix = "zstd-%s" % ZSTD_VERSION,
        urls = [
            "https://github.com/facebook/zstd/archive/%s.tar.gz" % ZSTD_VERSION,
        ],
    )
