import argparse

from tools.generators.cc_generator.utils import CCGEN_VERSION


def get_args() -> argparse.Namespace:
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
        description=("Generate C++ binaries, libraries, and tests within the")
        + " context of a Bazel workspace with initial boilerplate"
        " scaffolding.",
        epilog=("Specify a label for the library similar to how you would")
        + " specify a label for a cc_library rule.\n\nExample:"
        " `//foo/bar:baz`" + " will generate a library named baz in the foo/bar"
        " directory. The" + " library will contain a BUILD file with a cc_library rule"
        " for a .cc" + " file and associated .h file.",
    )
    parser.add_argument(
        "type",
        choices=["lib", "bin", "test"],
        help=(
            "The type of target to generate. lib: a cc_library rule. bin: a"
            + " cc_binary rule. test: a cc_test rule."
        ),
    )
    parser.add_argument(
        "label",
        help=("The label for the library to generate (e.g. //foo/bar:baz)."),
    )
    parser.add_argument(
        "-c",
        "--default_class",
        action="store_true",
        help=(
            "generate a default class definition within the library.(e.g. a"
            + " class Baz { public: Baz(); ~Baz(); };) This is only"
            " applicable to" + " libraries. [default: false]"
        ),
    )
    parser.add_argument(
        "-D",
        "--deps",
        help=(
            "a comma-separated list of dependencies for the"
            " generated target. [default: None]"
        ),
    )
    parser.add_argument(
        "-f",
        "--force",
        action="store_true",
        help=(
            "force generation of the target even if it already"
            " exists. [default: false]"
        ),
    )
    parser.add_argument(
        "-d",
        "--dry_run",
        action="store_true",
        help=(
            "print the generated files to stdout without writing them"
            " to disk. [default: false]"
        ),
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="show verbose output [default: false]",
    )
    parser.add_argument(
        "-V",
        "--version",
        action="version",
        version=f"%(prog)s {CCGEN_VERSION}",
    )

    return parser.parse_args()
