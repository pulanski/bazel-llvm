#pragma once

#include <iostream>
#include <memory>

#include "src/ast/expr_ast.h"
#include "src/ast/prototype_ast.h"

using namespace std;

/// Internal logger for general user-facing error messages
void logError(const string& message);

// TODO: Add more specific error messages
/// Internal logger for user-facing error messages with location information

/// Internal logger for general user-facing warning messages
void logWarning(const string& message);

/// Internal logger for general user-facing information messages
void logInfo(const string& message);

/// Logs syntax-based error messages to the user
unique_ptr<ExprAST> logSyntaxError(const string& message);

/// Logs prototype-specific syntax-based error messages to the user
unique_ptr<PrototypeAST> logPrototypeSyntaxError(const string& message);

/// Logs code generation-based error messages to the user
llvm::Value* logCodegenError(const string& message);
