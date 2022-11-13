#include "call_expr_ast.h"

#include <vector>

// Generate LLVM code for function calls
llvm::Value* CallExprAST::codegen() {
    llvm::Function* CalleeF = TheModule->getFunction(callee_);

    if (!CalleeF) {
        return logCodegenError("Unknown function referenced");
    }

    if (CalleeF->arg_size() != args_.size()) {
        return logCodegenError("Incorrect # arguments passed");
    }

    vector<llvm::Value*> argsV;

    for (unsigned i = 0, e = args_.size(); i != e; i++) {
        argsV.push_back(args_[i]->codegen());

        if (!argsV.back()) {
            return nullptr;
        }
    }

    return Builder.CreateCall(CalleeF, argsV, "calltmp");
}
