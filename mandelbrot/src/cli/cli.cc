#include "cli.h"

#include <iostream>

// #include "absl/status/status.h"
#include "fmt/color.h"
#include "glog/logging.h"
#include "mandelbrot/src/logger/logger.h"
#include "mandelbrot/src/utils/utils.h"
#include "third_party/cli11/cli11.h"

using namespace fmt;

int parseCommandLineArgs(int argc, char* argv[],
                         shared_ptr<MandelbrotCLI> mandelbrot_cli) {
    LOG(INFO) << "Initializing CLI...";

    StatusOr<string> versionResult = getMandelbrotVersion();
    if (versionResult.ok()) {
        mandelbrot_cli->mandelbrotVersion = versionResult.value();
    } else {
        LOG(ERROR) << "Could not get mandelbrot version: "
                   << versionResult.status();
        logErrorAndExit("Could not get mandelbrot version");
    }

    CLI::App cli{
        format(
            "Mandelbrot v{}\n\nJIT compiler for Mandelbrot source files. May "
            "be "
            "invoked as a REPL or with a file to compile. More information at "
            "<https://docs.mandelbrot-lang.org/learn/getting-started/>.\n",
            mandelbrot_cli->mandelbrotVersion),
        "mandelbrot"};

    cli.set_version_flag(
        "-v,--version",
        format("mandelbrot version {}", mandelbrot_cli->mandelbrotVersion));

    // Optional flags
    cli.add_flag("-d,--debug", mandelbrot_cli->cliOptions.debug_mode,
                 "Enable debug mode");
    cli.add_flag("-V,--verbose", mandelbrot_cli->cliOptions.verbose_output,
                 "Enable verbose mode");
    cli.add_flag("-e,--eval", mandelbrot_cli->cliOptions.verbose_output,
                 "Evaluate the given expression");
    cli.add_flag("-t,--emit-tokens", mandelbrot_cli->cliOptions.emit_tokens,
                 "Emit tokens created by the "
                 "lexer");
    cli.add_flag("-a,--emit-ast", mandelbrot_cli->cliOptions.emit_ast,
                 "Emit AST nodes");
    cli.add_flag("-i,--emit-ir", mandelbrot_cli->cliOptions.emit_ir,
                 "Emit LLVM IR");

    // Positional arguments
    cli.add_option("files", mandelbrot_cli->cliPositionals.files,
                   "Files to compile and execute");

    CLI11_PARSE(cli, argc, argv);

    LOG(INFO) << "Successfully parsed command line arguments";
    LOG(INFO) << "CLI options:\n" << mandelbrot_cli->toString();
    return 0;
}

shared_ptr<MandelbrotCLI> mandelbrotCLI = make_shared<MandelbrotCLI>();
