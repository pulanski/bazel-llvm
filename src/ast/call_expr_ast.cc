#include "call_expr_ast.h"

#include <cstddef>
#include <sstream>
#include <vector>

// Generate LLVM code for function calls
Value* CallExprAST::codegen() {
    Function* CalleeF = TheModule->getFunction(callee_);

    if (!CalleeF) {
        return logCodegenError(string("Unknown function ") + callee_ +
                               "referenced");
    }

    if (CalleeF->arg_size() != args_.size()) {
        stringstream errorMessage;
        errorMessage << "Incorrect number of arguments passed, expected "
                     << CalleeF->arg_size() << ", but instead found "
                     << args_.size() << ".";

        return logCodegenError(errorMessage.str());
    }

    vector<Value*> argsV;

    for (auto& arg : args_) {
        argsV.push_back(arg->codegen());

        if (!argsV.back()) {
            return nullptr;
        }
    }

    return Builder->CreateCall(CalleeF, argsV, "calltmp");
}
