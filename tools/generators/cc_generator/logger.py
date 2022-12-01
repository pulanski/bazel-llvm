import argparse
import os

from colored import attr, bg, fg

from tools.generators.cc_generator.utils import (
    WORKSPACE_DIR,
    create_generated_contents,
    get_relative_paths,
    parse_label,
)


def info(message: str):
    """Print an info message to stdout.

    Args:
        message (str): the message to print
    """
    print(f'{fg("black")}{bg("yellow")} INFO {attr("reset")}' + " " + message)


def error(message: str):
    """Print an error message to stderr and exit with a non-zero exit code.

    Args:
        message (str): the message to print
    """
    print(f'{fg("black")}{bg("red")} ERROR {attr("reset")}' + " " + message)
    exit(1)


def log_generated_contents(contents: str):
    """Print the contents of a file to stdout.

    Args:
        `contents (str)`: the contents of the file to print
    """

    print(f"{fg('grey_69')}Contents:{attr('reset')}")
    print(f"{fg('cyan')}\n{contents}\n{attr('reset')}")


def log_dry_run_and_exit():
    """Print a note to the user that no files were written to disk and exit."""

    print(
        f"\n{bg('yellow')} DRY RUN {attr('reset')} {fg('grey_69')}No"
        " files were written to disk. Re-run without the"
        f" `{fg('black')}--{fg('yellow')}dry_run{fg('grey_69')}` flag"
        f" to write files to disk.{attr('reset')}",
    )
    exit(0)


def log_generated_target(args: argparse.Namespace):
    """Logs the target to be generated to the user.

    Args:
        `args (argparse.Namespace)`: the parsed command line arguments
    """

    relative_dir, target = parse_label(args.label)

    match args.type:
        case "lib":
            info(
                f'{fg("grey_69")}Generating{fg("dark_orange_3a")} library'
                f' target{fg("yellow")} {args.label}{fg("grey_69")} in'
                " directory"
                f' {fg("green")}{relative_dir}{fg("grey_69")} with'
                f' target {fg("blue")}:{target}{attr("reset")}',
            )
        case "bin":
            info(
                f'{fg("grey_69")}Generating{fg("red")} binary'
                f' target{fg("yellow")} {args.label}{fg("grey_69")} in'
                " directory"
                f' {fg("green")}{relative_dir}{fg("grey_69")} with'
                f' target {fg("blue")}:{target}{attr("reset")}',
            )
        case "test":
            info(
                f'{fg("grey_69")}Generating{fg("medium_spring_green")} test'
                f' target{fg("yellow")} {args.label}{fg("grey_69")} in'
                " directory"
                f' {fg("green")}{relative_dir}{fg("grey_69")} with'
                f' target {fg("blue")}:{target}{attr("reset")}',
            )


def log_library_generation(
    relative_dir: str,
    args: argparse.Namespace,
):
    # TODO refactor here to general `log_generated_target` function
    """
    Logs the library generation to the user.

    Args:
        `relative_dir (str)`:           the relative directory of the target
        `args (argparse.Namespace)`:    the parsed command line arguments
    """
    (
        _,
        relative_build_file_path,
        relative_cc_header_path,
        relative_cc_source_path,
    ) = get_relative_paths(args.label, relative_dir)

    print(relative_cc_header_path, relative_cc_source_path)

    absolute_build_file_path = os.path.join(WORKSPACE_DIR, relative_build_file_path)

    (
        cc_build_file_contents,
        cc_header_contents,
        cc_source_contents,
    ) = create_generated_contents(
        args.label,
        args,
        relative_cc_header_path,
        relative_cc_source_path,
        relative_build_file_path,
    )

    # library file
    info(
        f"{fg('grey_69')}Creating"
        f" {fg('green')}{relative_cc_source_path}{fg('black')} ...",
    )
    if args.verbose:
        log_generated_contents(cc_source_contents)

    # header file
    info(
        f"{fg('grey_69')}Creating"
        f" {fg('green')}{relative_cc_header_path}{fg('black')} ...",
    )
    if args.verbose:
        log_generated_contents(cc_header_contents)

    # build file
    if os.path.exists(absolute_build_file_path):
        info(
            f"{fg('grey_69')}Appending to"
            f" {fg('green')}{relative_build_file_path}{fg('black')} ...",
        )
    else:
        info(
            f"{fg('grey_69')}Creating"
            f" {fg('green')}{relative_build_file_path}{fg('black')} ...",
        )

    if args.verbose:
        log_generated_contents(cc_build_file_contents)

    if args.dry_run:
        log_dry_run_and_exit()
    # info(f"Generating library in {relative_dir} with target {target}...")
    # if args.default_class:
    #     info("Generating default class definition...")
