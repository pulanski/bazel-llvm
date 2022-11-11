#pragma once

#include <utility>

#include "ExprAST.h"

using namespace std;

// Expression class for referencing a variable
class BinaryExprAST : ExprAST {
    char op_;
    unique_ptr<ExprAST> lhs_, rhs_;

   public:
    BinaryExprAST(char op, unique_ptr<ExprAST> lhs, unique_ptr<ExprAST> rhs)
        : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
};
