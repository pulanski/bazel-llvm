import argparse
import os
from typing import List, Tuple

BAZEL_BUILD_FILE = "BUILD.bazel"
CC_LIBRARY_LOAD_STATEMENT = 'load("@rules_cc//cc:defs.bzl", "cc_library")'
# get $BUILD_WORKSPACE_DIRECTORY from the environment
# (the directory where the bazel workspace is located on
# the host machine)
WORKSPACE_DIR = os.environ.get("BUILD_WORKSPACE_DIRECTORY", os.getcwd())
CCGEN_VERSION = "0.0.1"


############################
# General helper functions #
############################


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


def get_relative_paths(
    label: str,
    generator_type: str,
) -> Tuple[str, str, str]:
    """
    Get the relative paths to the BUILD file, header file, and source
    file for a given label.

    Args:
        `label`: the label of the target to generate
        `type`: The type of the target.

    Returns:
        A tuple of `(relative_dir, build_file_path, header_file_path, source_file_path)`
    """

    (package, target) = parse_label(label)

    relative_dir = os.path.join(*package.split("/"))
    build_file_path = os.path.join(package, BAZEL_BUILD_FILE)
    header_file_path = os.path.join(target, f"{target}.h")

    if generator_type == "lib" or generator_type == "bin":
        source_file_path = os.path.join(target, f"{target}.cc")
    else:  # type == "test"
        source_file_path = os.path.join(target, f"{target}_test.cc")
    return (relative_dir, build_file_path, header_file_path, source_file_path)


def get_absolute_paths(
    label: str,
    generator_type: str,
) -> Tuple[str, str, str]:
    """Get the absolute paths to the BUILD file, header file, and source
    file for a given label and type (lib, bin, or test).

    Args:
        `label`: the label of the target to generate
        `generator_type`: The type of the generated target (lib, bin, test).

    Returns:
        A tuple of `(absolute_dir, absolute_build_path, absolute_header_path,
        absolute_source_path)`
    """

    package, target = parse_label(label)
    (
        relative_dir,
        relative_build_path,
        _,  # relative_header_path
        _,  # relative_source_path
    ) = get_relative_paths(label, generator_type)

    absolute_dir = os.path.join(WORKSPACE_DIR, relative_dir)
    absolute_build_path = os.path.join(WORKSPACE_DIR, relative_build_path)

    absolute_header_path = os.path.join(WORKSPACE_DIR, package, f"{target}.h")
    if generator_type == "lib" or generator_type == "bin":
        absolute_source_path = os.path.join(WORKSPACE_DIR, package, f"{target}.cc")
    else:  # type == "test"
        absolute_source_path = os.path.join(WORKSPACE_DIR, package, f"{target}_test.cc")

    return (
        absolute_dir,
        absolute_build_path,
        absolute_header_path,
        absolute_source_path,
    )


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


########################################
# Helpers for generating file contents #
########################################


def create_generated_contents(
    label: str,
    args: argparse.Namespace,
    absolute_cc_header_path: str,
    absolute_cc_source_path: str,
    absolute_cc_build_path: str,
) -> List[str]:
    """
    Get the contents of a newly generated `cc_binary`, `cc_library`, or `cc_test`.

    Args:
        `label (str)`:                      the label of the target to generate
        `args (argparse.Namespace)`:        the parsed command line arguments
        `absolute_cc_header_path (str)`:    the absolute path to the
                                            generated header file
        `absolute_cc_library_path (str)`:   the absolute path to the
                                            generated binary / library file
        `absolute_cc_build_path (str)`:     the absolute path to the
                                            generated BUILD file

    Returns:
        A list of strings representing the contents of the generated
        `cc_binary`, `cc_library`, or `cc_test`.
    """

    match args.type:
        case "lib":
            return generated_cc_library_contents(
                label,
                args,
                absolute_cc_header_path,
                absolute_cc_source_path,
                absolute_cc_build_path,
            )
        case _:
            return []


def generated_cc_library_contents(
    label: str,
    args: argparse.Namespace,
    # absolute_cc_header_path: str,
    # absolute_cc_source_path: str,
    # absolute_cc_build_path: str,
) -> List[str]:
    """
    Get the contents of a newly generated `cc_library`.

    Args:
        `label (str)`:                      the label of the target to generate
        `args (argparse.Namespace)`:        the parsed command line arguments
        `absolute_cc_header_path (str)`:    the absolute path to the
                                            generated header file
        `absolute_cc_library_path (str)`:   the absolute path to the
                                            generated binary / library file
        `absolute_cc_build_path (str)`:     the absolute path to the
                                            generated BUILD file

    Returns:
        A list of strings representing the contents of the generated
        `cc_library`.
    """

    (_, target) = parse_label(label)

    if args.default_class:
        header_contents = f"""#pragma once

class {target.title()} {{
public:
    {target.title()}();
    ~{target.title()}();
}};"""
        source_contents = f"""#include "{target}.h"

{target.title()}::{target.title()}() {{}}"""
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
