#pragma once

#include <memory>
#include <string>
#include <vector>

#include "expr_ast.h"

using namespace std;

// Expression class for function calls
class CallExprAST : public ExprAST {
    string callee_;
    vector<unique_ptr<ExprAST>> args_;

   public:
    CallExprAST(const string& callee, vector<unique_ptr<ExprAST>> args)
        : callee_(callee), args_(std::move(args)) {}
};