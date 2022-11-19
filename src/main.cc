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

// Main driver code.
int main(int argc, char* argv[]) {
    // Initialize Glog
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Begin REPL...";

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
