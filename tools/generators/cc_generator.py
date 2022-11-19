import argparse
import os

from colored import attr, bg, fg

BAZEL_WORKSPACE_DIRECTORY_ENV = "BUILD_WORKSPACE_DIRECTORY"
BAZEL_BUILD_FILE = "BUILD.bazel"


def debug(message):
    print(f'{fg("black")}{bg("chartreuse_4")} DEBUG {attr("reset")}' + " " + message)


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
    "-v",
    "--verbose",
    action="store_true",
    help="show verbose output [default: false]",
)

args = parser.parse_args()
type, label, default_class, verbose = (
    args.type,
    args.label,
    args.default_class,
    args.verbose,
)

# parse the label
if label.startswith("//"):
    label = label[2:]
# split the label into a directory and a name
if label.find(":") != -1:
    directory, target = label.split(":")
else:
    directory, target = label, label.split("/")[-1]

if verbose:
    match type:
        case "lib":
            debug(
                f'{fg("grey_69")}Generating{fg("red")} library{fg("yellow")} {label}{fg("grey_69")} in directory {fg("green")}{directory}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
            )
        case "bin":
            debug(
                f'{fg("grey_69")}Generating{fg("red")} binary{fg("yellow")} {label}{fg("grey_69")} in directory {fg("green")}{directory}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
            )
        case "test":
            debug(
                f'{fg("grey_69")}Generating{fg("medium_spring_green")} test{fg("yellow")} {label}{fg("grey_69")} in directory {fg("green")}{directory}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
            )

# get $BUILD_WORKSPACE_DIRECTORY from the environment
workspace = os.environ.get(BAZEL_WORKSPACE_DIRECTORY_ENV)

# append the directory to the workspace
desired_dir = os.path.join(workspace, directory)
print("Desired leaf directory is", desired_dir)
os.makedirs(desired_dir, exist_ok=True)

# check if the build file exists
if os.path.isfile(os.path.join(desired_dir, "BUILD.bazel")):
    print("BUILD file already exists in", desired_dir)
    desired_path = os.path.join(desired_dir, "BUILD.bazel")
# else:


# f = open("demofile2.txt", "a") # append to file
