#pragma once

#include "ExprAST.h"

// Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
    double val_;

   public:
    NumberExprAST(double val) : val_(val) {}
};
