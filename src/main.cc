// #include <fmt/core.h>
#include <glog/logging.h>

#include <cstdio>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

// #include "absl/strings/str_join.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "logger/logger.h"
#include "parser/parser.h"

using namespace std;

/// top ::= definition | external | expression | ';'
static void mainLoop() {
    while (true) {
        fprintf(stderr, "ready> ");
        switch (curTok) {
            case TokEof:
                return;
            case ';':  // ignore top-level semicolons.
                getNextToken();
                break;
            case TokDef:
                handleDefinition();
                break;
            case TokExtern:
                handleExtern();
                break;
            default:
                handleTopLevelExpression();
                break;
        }
    }

    LOG(INFO) << "exited";
}

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

    // Run the main "interpreter loop" now.
    mainLoop();

    return 0;
}
