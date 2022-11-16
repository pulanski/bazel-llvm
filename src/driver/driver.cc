#include "src/driver/driver.h"

#include <kaleidoscope.h>

#include <memory>

#include "src/parser/parser.h"

// Main loop

/// top ::= definition | external | expression | ';'
void mainLoop() {
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
}

//////////////////////////////////////
// Top-level Parsing and JIT Driver //
//////////////////////////////////////

void handleDefinition() {
    if (auto fnDef = parseDefinition()) {
        logInfo("Successfully parsed a function definition.");
        if (auto fnIR = fnDef->codegen()) {
            fnIR->print(errs());
        }
    } else {
        // Skip the token for error recovery
        getNextToken();
    }
}

void handleExtern() {
    if (auto protoAST = parseExtern()) {
        logInfo("Successfully parsed an extern.");
        if (auto fnIR = protoAST->codegen()) {
            fnIR->print(errs());
        }
    } else {
        // Skip the token for error recovery
        getNextToken();
    }
}

void handleTopLevelExpression() {
    // Evaluate a top-level expression into an anonymous function.
    if (auto fnAST = parseTopLevelExpr()) {
        logInfo("Successfully parsed a top level expression.");
        if (auto* fnIR = fnAST->codegen()) {
            fnIR->print(errs());
            fprintf(stderr, "\n");
            // Remove the anonymous expression.
            fnIR->eraseFromParent();
        }
    } else {
        // Skip the token for error recovery
        getNextToken();
    }
}