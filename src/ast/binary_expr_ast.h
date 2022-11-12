#pragma once

#include <utility>

#include "expr_ast.h"

using namespace std;

// Expression class for referencing a variable
class BinaryExprAST : public ExprAST {
    char op_;
    unique_ptr<ExprAST> lhs_, rhs_;

   public:
    BinaryExprAST(char op, unique_ptr<ExprAST> lhs, unique_ptr<ExprAST> rhs)
        : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
};
