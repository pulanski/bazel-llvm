#include "number_expr_ast.h"

// Generate the LLVM IR for numeric literals
Value* NumberExprAST::codegen() {
    return ConstantFP::get(*TheContext, APFloat(val_));
}
