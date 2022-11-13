#include "variable_expr_ast.h"

// We assume that the variable has already been emitted somewhere
llvm::Value* VariableExprAST::codegen() {
    llvm::Value* V = NamedValues[name_];

    if (!V) {
        logCodegenError("Unknown variable name");
    }

    return V;
}
