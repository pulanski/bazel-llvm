#include <glog/logging.h>

#include <cstdio>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "driver/driver.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "logger/logger.h"
#include "parser/parser.h"
#include "passes/pass_manager.h"

using namespace std;

// Define externs

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

/// putchard - putchar that takes a double and returns 0.
extern "C" DLLEXPORT double putchard(double x) {
    fputc((char)x, stderr);
    return 0;
}

/// printd - printf that takes a double prints it as "%f\n", returning 0.
extern "C" DLLEXPORT double printd(double x) {
    fprintf(stderr, "%f\n", x);
    return 0;
}

// Main driver code.
int main(int argc, char* argv[]) {
    // Initialize Glog
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Begin REPL...";

    // Initialize LLVM JIT components
    initializeJIT();

    // Install standard binary operators.
    // 1 is lowest precedence.
    binOpPrecedence['<'] = 10;
    binOpPrecedence['+'] = 20;
    binOpPrecedence['-'] = 20;
    binOpPrecedence['*'] = 40;  // highest.

    // Prime the first token.
    fprintf(stderr, "ready> ");
    getNextToken();

    initializeModuleAndPassManager();

    // Run the main "interpreter loop" now.
    mainLoop();

    // Print out all of the generated code.
    TheModule->print(errs(), nullptr);

    return 0;
}
