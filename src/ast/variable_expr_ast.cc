#include "variable_expr_ast.h"

// We assume that the variable has already been emitted somewhere
Value* VariableExprAST::codegen() {
    Value* V = symbolTable[name_];

    if (!V) {
        logCodegenError("Unknown variable name " + name_);
    }

    return V;
}
