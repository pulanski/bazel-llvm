// #include <fmt/core.h>
#include <glog/logging.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "absl/strings/str_join.h"
#include "lexer/lexer.h"
#include "lexer/token.h"

using namespace std;

/// top ::= definition | external | expression | ';'
static void MainLoop() {
    while (true) {
        fprintf(stderr, "ready> ");
        switch (CurTok) {
            case TokEof:
                return;
            case ';':  // ignore top-level semicolons.
                // getNextToken();
                break;
            case TokDef:
                // HandleDefinition();
                break;
            case TokExtern:
                // HandleExtern();
                break;
            default:
                // HandleTopLevelExpression();
                break;
        }
    }
}

// Main driver code.
int main(int argc, char* argv[]) {
    // Initialize Glog
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "Begin REPL...";

    // Run the main "interpreter loop" now.
    // MainLoop();

    LOG(INFO) << "Lexing...";

    // vector<string> v = {"foo", "bar", "baz"};
    // string s = absl::StrJoin(v, "-");
    //
    // cout << "Joined string: " << s << "\n";
    return 0;
}
