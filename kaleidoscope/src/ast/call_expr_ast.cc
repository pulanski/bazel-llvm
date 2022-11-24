#include "call_expr_ast.h"

#include <cstddef>
#include <sstream>
#include <vector>

#include "kaleidoscope/src/ir_gen/ir_gen.h"

// Generate LLVM code for function calls
Value* CallExprAST::codegen() {
    Function* callee = getFunction(callee_);
    // Function* CalleeF = TheModule->getFunction(callee_);

    if (!callee) {
        return logCodegenError(string("Unknown function ") + callee_ +
                               " referenced");
    }

    if (callee->arg_size() != args_.size()) {
        stringstream errorMessage;
        errorMessage << "Incorrect number of arguments passed, expected "
                     << callee->arg_size() << ", but instead found "
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

    return Builder->CreateCall(callee, argsV, "calltmp");
}
