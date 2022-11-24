import argparse
import os
from typing import List, Tuple

BAZEL_BUILD_FILE = "BUILD.bazel"
CC_LIBRARY_LOAD_STATEMENT = 'load("@rules_cc//cc:defs.bzl", "cc_library")'
# get $BUILD_WORKSPACE_DIRECTORY from the environment
# (the directory where the bazel workspace is located on
# the host machine)
WORKSPACE_DIR = os.environ.get("BUILD_WORKSPACE_DIRECTORY")


def prepend_file(filename: str, contents: str):
    """Prepend contents to the beginning of a file.

    Args:
        `filename (str)`: the name of the file to prepend to
        `contents (str)`: the contents to prepend to the file
    """

    with open(filename, "r+") as f:
        existing_content = f.read()
        f.seek(0, 0)
        f.write(contents.rstrip("\r\n") + "\n" + existing_content)


def get_args():
    """Parse command line arguments.

    Returns:
        A tuple of (type, label, default_class, force, verbose) where:

        `type (str)`: the type of the target to generate
        `label (str)`: the label of the target to generate
        `default_class (str)`: the default class to use for the target
        `force (bool)`: whether to overwrite an existing target
        `verbose (bool)`: whether to print verbose output
    """

    parser = argparse.ArgumentParser(
        prog="ccgen",
        description="Generate C++ binaries, libraries, and tests within the context of a Bazel workspace with initial boilerplate scaffolding.",
        epilog="Specify a label for the library similar to how you would specify a label for a cc_library rule.\n\nExample: `//foo/bar:baz` will generate a library named baz in the foo/bar directory. The library will contain a BUILD file with a cc_library rule for a .cc file and associated .h file.",
    )
    parser.add_argument(
        "type",
        choices=["lib", "bin", "test"],
        help="The type of target to generate. lib: a cc_library rule. bin: a cc_binary rule. test: a cc_test rule.",
    )
    parser.add_argument(
        "label",
        help="The label for the library to generate (e.g. //foo/bar:baz).",
    )
    parser.add_argument(
        "-c",
        "--default_class",
        action="store_true",
        help="generate a default class definition within the library. (e.g. class Baz { public: Baz(); ~Baz(); };) This is only applicable to libraries. [default: false]",
    )
    # --deps (add a comma-separated list of dependencies to the generated target)
    parser.add_argument(
        "--deps",
        help="add a comma-separated list of dependencies to the generated target. [default: None]",
    )
    parser.add_argument(
        "-f",
        "--force",
        action="store_true",
        help="force generation of the target even if it already exists. [default: false]",
    )
    parser.add_argument(
        "-d",
        "--dry_run",
        action="store_true",
        help="print the generated files to stdout without writing them to disk. [default: false]",
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="show verbose output [default: false]",
    )

    return parser.parse_args()


def parse_label(label: str) -> Tuple[str, str]:
    """
    Parse a label into a tuple of (package, target).

    Args:
        label: The label to parse.

    Returns:
        A tuple of (package, target).
    """
    if label.startswith("//"):
        label = label[2:]
    if ":" in label:
        package, target = label.split(":")
    else:
        package = label
        target = os.path.basename(package)
    return (package, target)


def get_new_library_contents(target: str, default_class: bool) -> List[str]:
    if default_class:
        header_contents = f"""
        #pragma once

        class {target.title()} {{
        public:
            {target.title()}();
            ~{target.title()}();
        }};
        """
        source_contents = f"""
        #include "{target}.h"

        {target.title()}::{target.title()}() {{}}
        """
    else:
        header_contents = """#pragma once"""
        source_contents = f"""#include \"{target}.h\""""

    return [
        f"""cc_library(
    name = "{target}",
    srcs = ["{target}.cc"],
    hdrs = ["{target}.h"],
)""",
        header_contents,
        source_contents,
    ]
