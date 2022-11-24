#pragma once

#include <iostream>
#include <memory>

using namespace std;

/// Internal logger for general user-facing error messages
void logError(const string& message);

/// Log an error message and return the error code
void logErrorAndExit(const string& message, uint8_t error_code = 1);
// Example: logErrorAndExit("Unknown function referenced", 308); // Error code
// 308

// TODO: Add more specific error messages
/// Internal logger for user-facing error messages with location information

/// Internal logger for general user-facing warning messages
void logWarning(const string& message);

/// Internal logger for general user-facing information messages
void logInfo(const string& message);

// /// Logs syntax-based error messages to the user
// unique_ptr<ExprAST> logSyntaxError(const string& message);

// /// Logs prototype-specific syntax-based error messages to the user
// unique_ptr<PrototypeAST> logPrototypeSyntaxError(const string& message);

// /// Logs code generation-based error messages to the user
// llvm::Value* logCodegenError(const string& message);
