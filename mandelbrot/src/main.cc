#include <iostream>

#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "fmt/color.h"
#include "glog/logging.h"
#include "mandelbrot/src/cli/cli.h"
#include "mandelbrot/src/logger/logger.h"
#include "repl/repl.h"
#include "third_party/indicators/indicators.h"
#include "utils/utils.h"

using namespace std;
using namespace fmt;
using namespace indicators;
using namespace absl;
namespace fs = filesystem;

/// Defines the main function using `absl::Status` as the return type.
Status mandelbrotMain(int argc, char* argv[]) {
    mainDisplay();
    initializeRepl();
    mainLoop();

    return OkStatus();
}

/// Main entry point for the program. Handles parsing of command
/// line arguments and flags and then calls `mandelbrotMain`.
int main(int argc, char* argv[]) {
    // Initialize Glog
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Begin mandelbrot...";

    // Parse the command line args and initialize CLI
    parseCommandLineArgs(argc, argv, mandelbrotCLI);

    return mandelbrotMain(argc, argv).ok() ? 0 : 1;
}
