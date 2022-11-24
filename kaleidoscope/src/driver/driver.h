#pragma once

/// Driver routine for parsing definitions
/// and generating LLVM IR from the parsed AST node
void handleDefinition();

/// Driver routine for parsing externs
/// and generating LLVM IR from the parsed AST node
void handleExtern();

/// Driver routine for parsing top level expressions
/// and generating LLVM IR from the parsed AST node
void handleTopLevelExpression();

/// Main loop for the driver
void mainLoop();
