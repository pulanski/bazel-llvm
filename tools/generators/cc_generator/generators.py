import argparse
import os

from colored import fg

from tools.generators.cc_generator.logger import error, info, log_library_generation
from tools.generators.cc_generator.source_contents import GeneratedSourceContents
from tools.generators.cc_generator.utils import CC_LIBRARY_LOAD_STATEMENT, prepend_file


def generate_source_contents(
    args: argparse.Namespace,
    source_contents: GeneratedSourceContents,
):
    """Generates the source files for the given target type.

    Args:
        `args` (argparse.Namespace): The parsed command line arguments.
        `source_contents` (GeneratedSourceContents): The source files to generate.
    """

    match args.type:
        case "lib":
            generate_cc_library(args, source_contents)
        # case "bin":
        #     generate_cc_binary(args, source_contents)
        # case "test":
        #     generate_cc_test(args, source_contents)
        case _:
            error(f"Unreachable code reached in {__file__}")


def generate_cc_library(
    args: argparse.Namespace,
    source_contents: GeneratedSourceContents,
):
    """Generates a C++ library with the given label in the given directory.

    Args:
        `absolute_dir (str)`:           The absolute path to the directory in which
                                        to generate the library.
        `relative_dir (str)`:           The relative path to the directory in which
                                        to generate the library.
        `args (argparse.Namespace)`:    The parsed command line arguments.
    """

    # check if both the header and cc files already exist
    if os.path.exists(source_contents.header_file.absolute_path) and os.path.exists(
        source_contents.source_file.absolute_path,
    ):
        if args.force:
            info(
                f"{fg('grey_69')}`{fg('black')}--{fg('yellow')}force{fg('grey_69')}`"
                " flag is set, overwriting existing files",
            )
        else:
            error(
                f"{fg('grey_69')}Library file"
                f" {fg('green')}{source_contents.source_file.relative_path} {fg('grey_69')}or"
                " header file"
                f" {fg('green')}{source_contents.source_file.relative_path} {fg('grey_69')} already"
                " exists. Use"
                f" `{fg('black')}--{fg('yellow')}force{fg('grey_69')}`"
                " to overwrite them.",
            )

    log_library_generation(source_contents.relative_dir, args)

    if args.dry_run:
        return

    # create the directory if it doesn't exist
    os.makedirs(source_contents.absolute_dir, exist_ok=True)

    # if the build file exists, append to it
    if os.path.isfile(source_contents.build_file.absolute_path):
        # read the contents of the build file
        build_file = open(source_contents.build_file.absolute_path)
        existing_build_file_content = build_file.read()
        build_file.close()

        if existing_build_file_content.find(CC_LIBRARY_LOAD_STATEMENT) == -1:
            with open(source_contents.build_file.absolute_path, "r+") as build_file:
                prepend_file(
                    source_contents.build_file.absolute_path,
                    CC_LIBRARY_LOAD_STATEMENT,
                )
                build_file.close()

        if existing_build_file_content.find("package(default_visibility") == -1:
            with open(source_contents.build_file.absolute_path, "r+") as build_file:
                prepend_file(
                    source_contents.build_file.absolute_path,
                    "package(default_visibility =" ' ["//visibility:public"])\n',
                )
                build_file.close()
    else:
        # create the build file
        build_file = open(source_contents.build_file.absolute_path, "w")
        build_file.write(CC_LIBRARY_LOAD_STATEMENT + "\n\n")
        build_file.write(source_contents.build_file.contents)
        build_file.close()

    # create the library file
    cc_library_file = open(source_contents.source_file.absolute_path, "w")
    cc_library_file.write(source_contents.source_file.contents)
    cc_library_file.close()

    # create the header file
    cc_header_file = open(source_contents.header_file.absolute_path, "w")
    cc_header_file.write(source_contents.header_file.contents)
    cc_header_file.close()
