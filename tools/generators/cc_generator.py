import argparse
import os
import re
from typing import List

from colored import attr, bg, fg

BAZEL_WORKSPACE_DIRECTORY_ENV = "BUILD_WORKSPACE_DIRECTORY"
BAZEL_BUILD_FILE = "BUILD.bazel"

# get $BUILD_WORKSPACE_DIRECTORY from the environment
# (the directory where the bazel workspace is located on
# the host machine)
WORKSPACE_DIR = os.environ.get(BAZEL_WORKSPACE_DIRECTORY_ENV)


def info(message: str):
    print(f'{fg("black")}{bg("yellow")} INFO {attr("reset")}' + " " + message)


def error(message: str):
    print(f'{fg("black")}{bg("red")} ERROR {attr("reset")}' + " " + message)
    exit(1)


def get_args():
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

    args = parser.parse_args()
    return (
        args.type,
        args.label,
        args.default_class,
        args.force,
        args.dry_run,
        args.verbose,
    )


type, label, default_class, force, dry_run, verbose = get_args()


def get_new_library_contents(target: str) -> List[str]:
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
        header_contents = """
        #pragma once
        """
        source_contents = f"""
        #include "{target}.h"
        """

    return [
        f"""
        cc_library(
            name = "{target}",
            srcs = ["{target}.cc"],
            hdrs = ["{target}.h"],
        )
        """,
        header_contents,
        source_contents,
    ]


# def get_


def log_library_generation(relative_dir: str, target: str):
    relative_build_file_path = os.path.join(relative_dir, BAZEL_BUILD_FILE)
    relative_cc_library_path = os.path.join(relative_dir, target + ".cc")
    relative_cc_header_path = os.path.join(relative_dir, target + ".h")

    (
        cc_build_file_contents,
        cc_header_contents,
        cc_library_contents,
    ) = get_new_library_contents(target)

    info(
        f"{fg('grey_69')}Creating {fg('green')}{relative_cc_library_path}{fg('black')} ..."
    )
    if verbose:
        print(f"{fg('grey_69')}Contents:{attr('reset')}")
        print(f"{fg('cyan')}{cc_library_contents}{attr('reset')}")
    info(
        f"{fg('grey_69')}Creating {fg('green')}{relative_cc_header_path}{attr('reset')}"
    )
    if verbose:
        print(f"{fg('grey_69')}Contents:{attr('reset')}")
        print(f"{fg('cyan')}{cc_header_contents}{attr('reset')}")
    # check if the BUILD file already exists
    # if os.path.exists(os.path.join(workspace)
    info(
        f"{fg('grey_69')}Appending {fg('green')}{relative_build_file_path}{attr('reset')}"
    )
    if verbose:
        print(f"{fg('grey_69')}Contents:{attr('reset')}")
        print(f"{fg('cyan')}{cc_build_file_contents}{attr('reset')}")
    # info(f"Generating library in {relative_dir} with target {target}...")
    # if args.default_class:
    #     info("Generating default class definition...")


def generate_cc_library(absolute_dir: str, relative_dir: str, target: str):
    absolute_build_file_path = os.path.join(absolute_dir, BAZEL_BUILD_FILE)
    absolute_cc_library_path = os.path.join(absolute_dir, target + ".cc")
    absolute_cc_header_path = os.path.join(absolute_dir, target + ".h")

    relative_build_file_path = os.path.join(relative_dir, BAZEL_BUILD_FILE)
    relative_cc_library_path = os.path.join(relative_dir, target + ".cc")
    relative_cc_header_path = os.path.join(relative_dir, target + ".h")

    log_library_generation(relative_dir, target)

    # check if one of the library files already exists
    if os.path.exists(absolute_cc_library_path) or os.path.exists(
        absolute_cc_header_path
    ):
        if force:
            info("--force flag is set, overwriting existing files")
        else:
            error(
                f"Library files {relative_cc_library_path} or {relative_cc_header_path} already exist. Use --force to overwrite."
            )

    # check if the build file exists
    if os.path.isfile(absolute_build_file_path):
        if verbose:
            info(f"BUILD file already exists at {relative_build_file_path}")

        # read the contents of the build file
        build_file = open(absolute_build_file_path, "r")
        existing_build_file_content = build_file.read()
        build_file.close()

        if re.search(
            'load("@rules_cc//cc:defs.bzl", "cc_library")', existing_build_file_content
        ):
            with open(absolute_build_file_path, "r+") as build_file:
                build_file.seek(0, 2)
                # build_file.write(f"

    # if target in build_file_content:
    # if args.force:
    #     info("--force flag is set, overwriting existing target")
    #     build_file_content = build_file_content.replace(target, "")
    # else:
    #     error(
    #         f"Target {target} already exists in {relative_build_file_path}. Use --force to overwrite."
    #     )
    # else:


# parse the label
if label.startswith("//"):
    label = label[2:]
# split the label into a directory and a name
if label.find(":") != -1:
    relative_dir, target = label.split(":")
else:
    relative_dir, target = label, label.split("/")[-1]

# append the directory to the workspace
absolute_dir = os.path.join(WORKSPACE_DIR, relative_dir)
os.makedirs(absolute_dir, exist_ok=True)

match type:
    case "lib":
        if verbose:
            info(
                f'{fg("grey_69")}Generating{fg("dark_orange_3a")} library target{fg("yellow")} {label}{fg("grey_69")} in directory {fg("green")}{relative_dir}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
            )
        generate_cc_library(absolute_dir, relative_dir, target)
    case "bin":
        if verbose:
            info(
                f'{fg("grey_69")}Generating{fg("red")} binary target{fg("yellow")} {label}{fg("grey_69")} in directory {fg("green")}{relative_dir}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
            )
    case "test":
        if verbose:
            info(
                f'{fg("grey_69")}Generating{fg("medium_spring_green")} test target{fg("yellow")} {label}{fg("grey_69")} in directory {fg("green")}{relative_dir}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
            )
