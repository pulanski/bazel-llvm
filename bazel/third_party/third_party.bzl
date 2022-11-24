"""Third party library dependencies"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

# ZSTD_SHA = "188ba167e7a507b545c5f455af4afe3a34b2cee5551949fa000a8218ff4fda67"
# ZSTD_VERSION = "bd2740f3476c46b9f69d59e49e7391c2762e04b3"

def third_party_deps():
    """Fetches third party dependencies."""

    # Configure linenoise, a readline replacement.
    # See https://github.com/yhirose/cpp-linenoise for more details.
    maybe(
        http_archive,
        name = "com_github_yhirose_cpp_linenoise",
        build_file = "@com_pulanski_bazel_llvm//:bazel/third_party/zstd.BUILD",
        sha256 = "4cd89adfbc07cedada1aa32be12991828919d91b",
        # strip_prefix = "zstd-%s" % ZSTD_VERSION,
        # urls = [
        #     "https://github.com/facebook/zstd/archive/%s.tar.gz" % ZSTD_VERSION,
        # ],
    )
