#include "binary_expr_ast.h"

// Generate LLVM code for binary expressions
llvm::Value* BinaryExprAST::codegen() {
    llvm::Value* L = lhs_->codegen();
    llvm::Value* R = rhs_->codegen();

    if (!L || !R) {
        return nullptr;
    }

    switch (op_) {
        case '+':
            return Builder.CreateFAdd(L, R, "addtmp");
        case '-':
            return Builder.CreateFSub(L, R, "subtmp");
        case '*':
            return Builder.CreateFMul(L, R, "multmp");
        case '<':
            L = Builder.CreateFCmpULT(L, R, "cmptmp");
            return Builder.CreateUIToFP(L, llvm::Type::getDoubleTy(TheContext),
                                        "booltmp");
        default:
            return logCodegenError("Invalid binary operator");
    }
}
