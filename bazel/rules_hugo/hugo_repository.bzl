"""
Defines a hugo repository within the context of a Bazel workspace,
which effectively allows Bazel users to specify the version of Hugo
they want to use in their project and bring it in as a dependency.

Required due to build issues within rules_hugo implementation
(e.g. the hugo maintainers decided to change their naming conventions
for releases specifically in respect to MacOS in release version 102, which broke the rules_hugo implementation).
"""

HUGO_BUILD_FILE = """
package(default_visibility = ["//visibility:public"])
exports_files( ["hugo"] )
"""

def _hugo_repository_impl(repository_ctx):
    hugo = "hugo"
    if repository_ctx.attr.extended:
        hugo = "hugo_extended"

    os_arch = repository_ctx.attr.os_arch

    os_name = repository_ctx.os.name.lower()
    if os_name.startswith("mac os"):
        os_arch = "darwin-universal"
    elif os_name.find("windows") != -1:
        os_arch = "Windows-64bit"
    else:
        os_arch = "Linux-64bit"

    url = "https://github.com/gohugoio/hugo/releases/download/v{version}/{hugo}_{version}_{os_arch}.tar.gz".format(
        hugo = hugo,
        os_arch = os_arch,
        version = repository_ctx.attr.version,
    )

    repository_ctx.download_and_extract(
        url = url,
        sha256 = repository_ctx.attr.sha256,
    )

    repository_ctx.file("BUILD.bazel", HUGO_BUILD_FILE)

hugo_repository = repository_rule(
    _hugo_repository_impl,
    attrs = {
        "extended": attr.bool(
            doc = "Use extended hugo version",
        ),
        "os_arch": attr.string(
            doc = "The os arch value. If empty, autodetect it",
        ),
        "sha256": attr.string(
            doc = "The sha256 value for the binary",
        ),
        "version": attr.string(
            default = "0.55.5",
            doc = "The hugo version to use",
        ),
    },
)
