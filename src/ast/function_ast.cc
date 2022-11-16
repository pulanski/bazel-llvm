#include "function_ast.h"

#include "src/kaleidoscope/kaleidoscope.h"
#include "src/logger/logger.h"
#include "src/passes/pass_manager.h"

Function* FunctionAST::codegen() {
    // First, check for an existing function from a previous 'extern'
    // declaration.
    Function* fn = TheModule->getFunction(proto_->getName());

    if (!fn) {
        fn = proto_->codegen();
    }

    if (!fn) {
        return nullptr;
    }

    if (!fn->empty()) {
        return (Function*)logCodegenError("Function cannot be redefined.");
    }

    // Create a new basic block to start insertion into.
    BasicBlock* basicBlock = BasicBlock::Create(*TheContext, "entry", fn);
    Builder->SetInsertPoint(basicBlock);

    // Record the function arguments in the NamedValues map.
    symbolTable.clear();

    for (auto& arg : fn->args()) {
        symbolTable[string(arg.getName())] = &arg;
    }

    if (Value* retVal = body_->codegen()) {
        // Finish off the function.
        Builder->CreateRet(retVal);

        // Validate the generated code, checking for consistency.
        verifyFunction(*fn);

        // Optimize the function.
        TheFPM->run(*fn);

        return fn;
    }

    // Error reading body, remove function.
    fn->eraseFromParent();
    return nullptr;
}
