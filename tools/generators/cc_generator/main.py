from tools.generators.cc_generator.cli import get_args
from tools.generators.cc_generator.generators import generate_source_contents
from tools.generators.cc_generator.logger import log_generated_target
from tools.generators.cc_generator.source_contents import get_scaffolded_source_contents


def main():
    """Driver for `ccgen`. Handles generating C++ binaries (`cc_binary`),
    libraries (`cc_library`), and tests (`cc_test`) within the context of a Bazel
    workspace including initial boilerplate scaffolding."""

    args = get_args()
    log_generated_target(args)

    source_contents = get_scaffolded_source_contents(args)
    generate_source_contents(args, source_contents)


main()
