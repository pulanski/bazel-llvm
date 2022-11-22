#include "function_ast.h"

#include "src/globals/globals.h"
#include "src/ir_gen/ir_gen.h"
#include "src/logger/logger.h"
#include "src/passes/pass_manager.h"

Function* FunctionAST::codegen() {
    // Transfer ownership of the prototype to the FunctionProtos map, but keep a
    // reference to it for use below.
    auto& p = *proto_;
    functionProtos[proto_->getName()] = std::move(proto_);

    // First, check for an existing function from a previous 'extern'
    // declaration.
    Function* fn = getFunction(p.getName());

    if (!fn) {
        return nullptr;
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
