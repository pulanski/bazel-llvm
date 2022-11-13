#include "number_expr_ast.h"

// Generate the LLVM IR for numeric literals
llvm::Value* NumberExprAST::codegen() {
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(val_));
}
