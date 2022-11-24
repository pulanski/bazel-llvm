#pragma once

#include "expr_ast.h"
#include "kaleidoscope/src/globals/globals.h"

// Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
    double val_;

   public:
    NumberExprAST(double val) : val_(val) {}
    auto codegen() -> Value* override;
};
