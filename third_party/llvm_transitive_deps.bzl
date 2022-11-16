"""External dependencies for llvm."""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

ZLIB_SHA = "b3a24de97a8fdbc835b9833169501030b8977031bcb54b3b3ac13740f846ab30"
ZLIB_VERSION = "1.2.13"

ZSTD_SHA = "188ba167e7a507b545c5f455af4afe3a34b2cee5551949fa000a8218ff4fda67"
ZSTD_VERSION = "bd2740f3476c46b9f69d59e49e7391c2762e04b3"

def llvm_transitive_deps():
    """Fetches transitive dependencies (zlib and zstd, used for compression in optimization passes) of LLVM for header generation."""

    # Configure zlib, a compression library for C/C++
    # See https://github.com/madler/zlib for more details.
    maybe(
        http_archive,
        name = "zlib",
        build_file = "@com_pulanski_bazel_llvm//:third_party/zlib.BUILD",
        sha256 = ZLIB_SHA,
        strip_prefix = "zlib-%s" % ZLIB_VERSION,
        urls = [
            "https://mirror.bazel.build/zlib.net/zlib-%s.tar.gz" % ZLIB_VERSION,
            "https://zlib.net/zlib-%s.tar.gz" % ZLIB_VERSION,
        ],
    )

    # Configure zstd, a real-time compression library for C/C++
    # See https://github.com/facebook/zstd for more details.
    maybe(
        http_archive,
        name = "zstd",
        build_file = "@com_pulanski_bazel_llvm//:third_party/zstd.BUILD",
        sha256 = ZSTD_SHA,
        strip_prefix = "zstd-%s" % ZSTD_VERSION,
        urls = [
            "https://github.com/facebook/zstd/archive/%s.tar.gz" % ZSTD_VERSION,
        ],
    )
