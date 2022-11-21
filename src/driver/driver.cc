#include "src/driver/driver.h"

#include <globals.h>

#include <memory>

#include "src/globals/globals.h"
#include "src/parser/parser.h"
#include "src/passes/pass_manager.h"

using namespace llvm;
using namespace llvm::orc;

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
            // TODO if emit_llvm is set, print the IR
            fnIR->print(errs());
            fprintf(stderr, "\n");

            // Create a ResourceTracker to track JIT'd memory allocated to our
            // anonymous expression -- that way we can free it after executing.
            auto resourceTracker =
                TheJIT->getMainJITDylib().createResourceTracker();

            auto threadSafeModule =
                ThreadSafeModule(std::move(TheModule), std::move(TheContext));

            ExitOnErr(TheJIT->addModule(std::move(threadSafeModule),
                                        resourceTracker));

            // Open a new module to hold subsequent code generation
            // since the module is now owned by the JIT.
            initializeModuleAndPassManager();

            // Search the JIT for the __anon_expr symbol.
            auto exprSymbol = ExitOnErr(TheJIT->lookup("__anon_expr"));

            // TODO add more error codes and ability to look up error codes
            if (!exprSymbol) {
                logErrorAndExit("Could not find expression during JIT lookup.",
                                1);
            }

            // Get the symbol's address and cast it to the right type (takes no
            // arguments, returns a double) so we can call it as a native
            // function.
            double (*fp)() = (double (*)())(intptr_t)exprSymbol.getAddress();
            fprintf(stderr, "%f\n", fp());

            // Delete the anonymous expression module from the JIT.
            ExitOnErr(resourceTracker->remove());
        }
    } else {
        // Skip the token for error recovery
        getNextToken();
    }
}
