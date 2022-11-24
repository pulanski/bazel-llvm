"""
Bazel rule for bringing **LLVM build definitions** into Bazel's sandbox environment

Brings **LLVM** into the scope of a bazel workspace.
This rule brings **LLVM** into the scope of a bazel workspace file primarily
designed for usage within **C++ binaries and libraries** (e.g. `cc_binary`,
`cc_library`). This is done by declaring `@llvm` as a dependency in your `BUILD`
files. With `@llvm` declared as a dependency you can then use LLVM classes, header
files, etc. in your project (e.g. `#include "llvm/IR/Value.h"`).

**Args**:

  _name_: A string. Name of the rule.

  _version_: A string. The version of LLVM to use (e.g. `15.0.4`, `14.0.0`, etc.) (Check
  https://github.com/llvm/llvm-project/releases for more details)

  _os_arch_: A string. The OS and CPU architecture combination to build for (e.g.
  `arm64-apple-darwin21.0`, `powerpc64le-linux-ubuntu-18.04.5`) (Check
  https://github.com/llvm/llvm-project/releases for more details)
"""

LLVM_VERSION = "15.0.4"
OS_ARCH = "arm64-apple-darwin21.0"

def _impl(ctx):
    """
    Implementation of the llvm() rule. Downloads and extracts the pre-built LLVM binaries and compiles them into a cc_library().
    """

    # Download the pre-built LLVM binaries.
    version = ctx.attr.version
    name = "clang+llvm-%s-%s" % (ctx.attr.version, ctx.attr.os_arch)
    # name = "clang+llvm-%s-%s" % (version, OS_ARCH)

    # https://github.com/llvm/llvm-project/releases/download/llvmorg-15.0.4/clang+llvm-15.0.4-arm64-apple-darwin21.0.tar.xz
    ctx.download_and_extract(
        # url = "https://releases.llvm.org/%s/%s.tar.xz" % (version, name), <- old releases hosting location
        url = "https://github.com/llvm/llvm-project/releases/download/llvmorg-%s/%s.tar.xz" % (version, name),
    )

    # Create a bash wrapper of llc to invoke it from Bazel.
    ctx.file("llc_runner.sh", """
# --- begin runfiles.bash initialization ---
if [[ ! -d "${RUNFILES_DIR:-/dev/null}" && ! -f "${RUNFILES_MANIFEST_FILE:-/dev/null}" ]]; then
    if [[ -f "$0.runfiles_manifest" ]]; then
      export RUNFILES_MANIFEST_FILE="$0.runfiles_manifest"
    elif [[ -f "$0.runfiles/MANIFEST" ]]; then
      export RUNFILES_MANIFEST_FILE="$0.runfiles/MANIFEST"
    elif [[ -f "$0.runfiles/bazel_tools/tools/bash/runfiles/runfiles.bash" ]]; then
      export RUNFILES_DIR="$0.runfiles"
    fi
fi
if [[ -f "${RUNFILES_DIR:-/dev/null}/bazel_tools/tools/bash/runfiles/runfiles.bash" ]]; then
  source "${RUNFILES_DIR}/bazel_tools/tools/bash/runfiles/runfiles.bash"
elif [[ -f "${RUNFILES_MANIFEST_FILE:-/dev/null}" ]]; then
  source "$(grep -m1 "^bazel_tools/tools/bash/runfiles/runfiles.bash " \
            "$RUNFILES_MANIFEST_FILE" | cut -d ' ' -f 2-)"
else
  echo >&2 "ERROR: cannot find @bazel_tools//tools/bash/runfiles:runfiles.bash"
  exit 1
fi
# --- end runfiles.bash initialization ---
# Pass through invocation to the underlying llc binary
$(rlocation %s/external/llvm/%s/bin/llc) $@
""" % (ctx.attr.workspace_name, name))

    # Create a BUILD file exporting the LLVM libraries and an llc binary.
    ctx.file("BUILD", """
package(default_visibility = ["//visibility:public"])
# Include all LLVM code into the single target
cc_library(
    name = "llvm",
    # Don't include lib/ recursively, because we don't want all the clang code in there.
    srcs = glob(["%s/lib/*.a"]),
    hdrs = glob([
        "%s/include/**/*.h",
        "%s/include/**/*.inc",
        "%s/include/**/*.def",
        "%s/include/**/*.gen",
    ]),
    includes = ["%s/include/"],
    linkopts = [
        "-lpthread",
        "-lcurses",
        "-ldl",
    ],
)
# Wrap llc in a Bazel invocable binary.
sh_binary(
    name = "llc",
    srcs = ["llc_runner.sh"],
    data = ["%s/bin/llc"],
    deps = ["@bazel_tools//tools/bash/runfiles"],
)
""" % (name, name, name, name, name, name, name))

    # Create a file for Starlark macros for LLVM.
    ctx.file("llvm.bzl", '''
def llc(name, src, out):
    """Invokes llc on the given src file and outputs it at the given out name."""
    native.genrule(
        name = name,
        srcs = [src],
        outs = [out],
        cmd = """
            $(location @llvm//:llc) < "$<" > "$@"
        """,
        tools = ["@llvm//:llc"],
    )
''')

    # Create an empty WORKSPACE file.
    ctx.file("WORKSPACE", "")

# Declare the rule to import LLVM from a WORKSPACE file.
llvm = repository_rule(
    implementation = _impl,
    attrs = {
        # The OS / CPU architecture combination to fetch for LLVM
        "os_arch": attr.string(default = OS_ARCH),
        # The version of LLVM to download.
        "version": attr.string(default = LLVM_VERSION),
        # The name of the workspace() this is being included in.
        "workspace_name": attr.string(mandatory = True),
    },
)
