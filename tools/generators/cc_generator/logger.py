import os

from colored import attr, bg, fg

from tools.generators.cc_generator.utils import (
    BAZEL_BUILD_FILE,
    WORKSPACE_DIR,
    get_new_library_contents,
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
        f"\n{bg('yellow')} DRY RUN {attr('reset')} {fg('grey_69')}No files were written to disk. Re-run without the `{fg('black')}--{fg('yellow')}dry_run{fg('grey_69')}` flag to write files to disk.{attr('reset')}"
    )
    exit(0)


def log_library_generation(
    relative_dir: str, target: str, default_class: bool, verbose: bool, dry_run: bool
):
    relative_build_file_path = os.path.join(relative_dir, BAZEL_BUILD_FILE)
    relative_cc_library_path = os.path.join(relative_dir, target + ".cc")
    relative_cc_header_path = os.path.join(relative_dir, target + ".h")

    absolute_build_file_path = os.path.join(WORKSPACE_DIR, relative_build_file_path)

    (
        cc_build_file_contents,
        cc_header_contents,
        cc_library_contents,
    ) = get_new_library_contents(target, default_class)

    # library file
    info(
        f"{fg('grey_69')}Creating {fg('green')}{relative_cc_library_path}{fg('black')} ..."
    )
    if verbose:
        log_generated_contents(cc_library_contents)

    # header file
    info(
        f"{fg('grey_69')}Creating {fg('green')}{relative_cc_header_path}{fg('black')} ...{attr('reset')}"
    )
    if verbose:
        log_generated_contents(cc_header_contents)

    # build file
    if os.path.exists(absolute_build_file_path):
        info(
            f"{fg('grey_69')}Appending to {fg('green')}{relative_build_file_path}{fg('black')} ...{attr('reset')}"
        )
    else:
        info(
            f"{fg('grey_69')}Creating {fg('green')}{relative_build_file_path}{fg('black')} ...{attr('reset')}"
        )

    if verbose:
        log_generated_contents(cc_build_file_contents)

    if dry_run:
        log_dry_run_and_exit()
    # info(f"Generating library in {relative_dir} with target {target}...")
    # if args.default_class:
    #     info("Generating default class definition...")
