import argparse

from colored import attr, fg

from tools.generators.cc_generator.utils import (
    create_generated_contents,
    get_absolute_paths,
    get_relative_paths,
    parse_label,
)


class GeneratedFile:
    """A file that is generated by the generator.

    Contains the file's name, contents, relative and absolute paths.

    Attributes:
        `name (str)`:           the name of the file
        `contents (str)`:       the contents of the file
        `relative_path (str)`:  the relative path to the file
        `absolute_path (str)`:  the absolute path to the file
    """

    def __init__(
        self,
        name: str,
        contents: str,
        relative_path: str,
        absolute_path: str,
    ):
        self.name = name
        self.contents = contents
        self.relative_path = relative_path
        self.absolute_path = absolute_path

    def __str__(self):
        return "\n\n".join(
            [
                f"{fg('green')}{self.name}{attr('reset')}",
                f"{fg('grey_69')}Contents:\n\n{fg('cyan')}{self.contents}{attr('reset')}",
                f"{fg('grey_69')}Relative path: {fg('red')}{self.relative_path}{attr('reset')}",
                f"{fg('grey_69')}Absolute path: {fg('yellow')}{self.absolute_path}{attr('reset')}",
                "",
            ]
        )

    def __repr__(self):
        return f"{self.name} ({self.relative_path})"


class GeneratedSourceContents:
    """The contents of a newly generated `cc_binary`, `cc_library`, or `cc_test`.

    Contains the contents of the generated BUILD file, header file, and source file.

    Attributes:
        `relative_dir (str)`:           the relative path to the directory in which
                                        the source contents are generated
        `absolute_dir (str)`:           the absolute path to the directory in which
                                        the source contents are generated
        `build_file (GeneratedFile)`:   the generated BUILD file
        `header_file (GeneratedFile)`:  the generated header file
        `source_file (GeneratedFile)`:  the generated source file
    """

    def __init__(
        self,
        relative_dir: str,
        absolute_dir: str,
        build_file: GeneratedFile,
        header_file: GeneratedFile,
        source_file: GeneratedFile,
    ):
        self.relative_dir = relative_dir
        self.absolute_dir = absolute_dir
        self.build_file = build_file
        self.header_file = header_file
        self.source_file = source_file

    def __str__(self):
        return "\n\n".join(
            [
                str(self.build_file),
                str(self.header_file),
                str(self.source_file),
            ]
        )

    def __repr__(self):
        return f"{self.build_file} {self.header_file} {self.source_file}"


def get_scaffolded_source_contents(
    args: argparse.Namespace,
) -> GeneratedSourceContents:
    """Gets the scaffolded contents of the source files to be generated.

    Args:
        `args (argparse.Namespace)`:    The parsed command line arguments.

    Returns:
        `GeneratedSourceContents`:      The contents of the source files to be
                                        generated.
    """

    (_, target) = parse_label(args.label)

    (
        relative_dir,
        relative_build_file_path,
        relative_cc_header_path,
        relative_cc_source_path,
    ) = get_relative_paths(args.label, args.type)

    (
        absolute_dir,
        absolute_build_file_path,
        absolute_cc_header_path,
        absolute_cc_source_path,
    ) = get_absolute_paths(args.label, args.type)

    (
        cc_build_file_contents,
        cc_header_contents,
        cc_library_contents,
    ) = create_generated_contents(
        args.label,
        args,
        absolute_cc_header_path,
        absolute_cc_source_path,
        absolute_build_file_path,
    )

    return GeneratedSourceContents(
        relative_dir=relative_dir,
        absolute_dir=absolute_dir,
        source_file=GeneratedFile(
            name="Source file: " + target + ".cc",
            contents=cc_library_contents,
            relative_path=relative_cc_source_path,
            absolute_path=absolute_cc_source_path,
        ),
        header_file=GeneratedFile(
            name="Header file: " + target + ".h",
            contents=cc_header_contents,
            relative_path=relative_cc_header_path,
            absolute_path=absolute_cc_header_path,
        ),
        build_file=GeneratedFile(
            name="Build file: BUILD.bazel",
            contents=cc_build_file_contents,
            relative_path=relative_build_file_path,
            absolute_path=absolute_build_file_path,
        ),
    )
