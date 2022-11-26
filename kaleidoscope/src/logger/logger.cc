#include "logger.h"

#include <cstdlib>
#include <iostream>

#include "fmt/color.h"

using namespace std;
using namespace fmt;

void logError(std::string_view message) {
    print(fg(color::black) | bg(color::crimson) | emphasis::bold, " ERROR ");
    print(" {}\n", message);
}

void logErrorAndExit(std::string_view message, uint8_t error_code = 1) {
    logError(format("E{} {}", error_code, message));
    exit(error_code);
}

void logWarning(std::string_view message) {
    print(fg(color::black) | bg(color::orange_red) | emphasis::bold,
          " WARNING ");
    print(" {}\n", message);
}

void logInfo(std::string_view message) {
    print(fg(color::black) | bg(color::yellow) | emphasis::bold, " INFO ");
    print(" {}\n", message);
}

unique_ptr<ExprAST> logSyntaxError(std::string_view message) {
    string syntax_error_message_header =
        format(fg(color::aqua), "Syntax Error");
    logError(format("{} {}", syntax_error_message_header, message));
    return nullptr;
}

unique_ptr<PrototypeAST> logPrototypeSyntaxError(std::string_view message) {
    string syntax_error_message_header =
        format(fg(color::aqua), "Syntax Error");
    string syntax_error_type =
        format(fg(color::light_yellow) | emphasis::italic, "Prototype");
    logError(format("{} {} {}", syntax_error_message_header, syntax_error_type,
                    message));
    return nullptr;
}

llvm::Value* logCodegenError(std::string_view message) {
    string codegen_error_message_header =
        format(fg(color::magenta), "Codegen Error");
    logError(format("{} {}", codegen_error_message_header, message));
    return nullptr;
}
