import os

from colored import attr, fg

from tools.generators.cc_generator.logger import error, info, log_library_generation
from tools.generators.cc_generator.utils import (
    BAZEL_BUILD_FILE,
    CC_LIBRARY_LOAD_STATEMENT,
    WORKSPACE_DIR,
    get_args,
    get_new_library_contents,
    parse_label,
    prepend_file,
)

# TODO refactor arg parsing into a class and pass
# the class around where needed


def generate_cc_library(
    absolute_dir: str,
    relative_dir: str,
    target: str,
    default_class: bool,
    verbose: bool,
    dry_run: bool,
    force: bool,
):
    absolute_build_file_path = os.path.join(absolute_dir, BAZEL_BUILD_FILE)
    absolute_cc_library_path = os.path.join(absolute_dir, target + ".cc")
    absolute_cc_header_path = os.path.join(absolute_dir, target + ".h")

    relative_cc_library_path = os.path.join(relative_dir, target + ".cc")
    relative_cc_header_path = os.path.join(relative_dir, target + ".h")

    (
        cc_build_file_contents,
        cc_header_contents,
        cc_library_contents,
    ) = get_new_library_contents(target, default_class)

    log_library_generation(relative_dir, target, default_class, verbose, dry_run)

    # check if one of the library files already exists
    if os.path.exists(absolute_cc_library_path) or os.path.exists(
        absolute_cc_header_path
    ):
        if force:
            info(
                f"`{fg('black')}--{fg('yellow')}force{fg('grey_69')}` flag is set, overwriting existing files"
            )
        else:
            error(
                f"{fg('grey_69')}Library file {fg('green')}{relative_cc_library_path} {fg('grey_69')}or header file {fg('green')}{relative_cc_header_path} {fg('grey_69')}already exists. Use `{fg('black')}--{fg('yellow')}force{fg('grey_69')}` to overwrite them."
            )

    # if the build file exists, append to it
    if os.path.isfile(absolute_build_file_path):
        # read the contents of the build file
        build_file = open(absolute_build_file_path, "r")
        existing_build_file_content = build_file.read()
        build_file.close()

        if existing_build_file_content.find(CC_LIBRARY_LOAD_STATEMENT) == -1:
            with open(absolute_build_file_path, "r+") as build_file:
                prepend_file(absolute_build_file_path, CC_LIBRARY_LOAD_STATEMENT)
                build_file.close()
    else:
        # create the build file
        build_file = open(absolute_build_file_path, "w")
        build_file.write(CC_LIBRARY_LOAD_STATEMENT + "\n\n")
        build_file.write(cc_build_file_contents)
        build_file.close()

    # create the library file
    cc_library_file = open(absolute_cc_library_path, "w")
    cc_library_file.write(cc_library_contents)
    cc_library_file.close()

    # create the header file
    cc_header_file = open(absolute_cc_header_path, "w")
    cc_header_file.write(cc_header_contents)
    cc_header_file.close()

    # if target in build_file_content:
    # if args.force:
    #     info("--force flag is set, overwriting existing target")
    #     build_file_content = build_file_content.replace(target, "")
    # else:
    #     error(
    #         f"Target {target} already exists in {relative_build_file_path}. Use --force to overwrite."
    #     )
    # else:


def main():
    """Driver for ccgen. Handles generating C++ binaries, libraries, and tests within the context of a Bazel workspace with initial boilerplate scaffolding."""

    args = get_args()

    relative_dir, target = parse_label(args.label)

    print(args.deps)

    # append the directory to the workspace
    absolute_dir = os.path.join(WORKSPACE_DIR, relative_dir)
    os.makedirs(absolute_dir, exist_ok=True)

    match args.type:
        case "lib":
            if args.verbose:
                info(
                    f'{fg("grey_69")}Generating{fg("dark_orange_3a")} library target{fg("yellow")} {args.label}{fg("grey_69")} in directory {fg("green")}{relative_dir}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
                )
            generate_cc_library(
                absolute_dir,
                relative_dir,
                target,
                args.default_class,
                args.verbose,
                args.dry_run,
                args.force,
            )
        case "bin":
            if args.verbose:
                info(
                    f'{fg("grey_69")}Generating{fg("red")} binary target{fg("yellow")} {args.label}{fg("grey_69")} in directory {fg("green")}{relative_dir}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
                )
        case "test":
            if args.verbose:
                info(
                    f'{fg("grey_69")}Generating{fg("medium_spring_green")} test target{fg("yellow")} {args.label}{fg("grey_69")} in directory {fg("green")}{relative_dir}{fg("grey_69")} with target {fg("blue")}:{target}{attr("reset")}'
                )


main()
