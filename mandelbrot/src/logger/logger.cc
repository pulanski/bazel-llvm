#include "logger.h"

#include <cstdlib>
#include <iostream>

#include "absl/strings/str_cat.h"
#include "fmt/color.h"

using namespace std;
using namespace fmt;
using namespace absl;

void logError(const string& message) {
    print(fg(color::black) | bg(color::crimson), " ERROR ");
    print(" {}\n", message);
}

void logErrorAndExit(const string& message, uint8_t error_code) {
    logError(StrCat(format(fg(color::crimson), "E{}", error_code),
                    format(fg(color::black), ": "),
                    format(emphasis::italic, "{}", message)));
    exit(error_code);
}

void logWarning(const string& message) {
    print(fg(color::black) | bg(color::orange_red) | emphasis::bold,
          " WARNING ");
    print(" {}\n", message);
}

void logInfo(const string& message) {
    print(fg(color::black) | bg(color::yellow) | emphasis::bold, " INFO ");
    print(" {}\n", message);
}

// unique_ptr<ExprAST> logSyntaxError(const string& message) {
//     string syntax_error_message_header =
//         format(fg(color::aqua), "Syntax Error");
//     logError(format("{} {}", syntax_error_message_header, message));
//     return nullptr;
// }

// unique_ptr<PrototypeAST> logPrototypeSyntaxError(const string& message) {
//     string syntax_error_message_header =
//         format(fg(color::aqua), "Syntax Error");
//     string syntax_error_type =
//         format(fg(color::light_yellow) | emphasis::italic, "Prototype");
//     logError(format("{} {} {}", syntax_error_message_header,
//     syntax_error_type,
//                     message));
//     return nullptr;
// }

// llvm::Value* logCodegenError(const string& message) {
//     string codegen_error_message_header =
//         format(fg(color::magenta), "Codegen Error");
//     logError(format("{} {}", codegen_error_message_header, message));
//     return nullptr;
// }
