#pragma once

#include <string>

#include "expr_ast.h"

using namespace std;

// Expression class for referencing a variable
class VariableExprAST : public ExprAST {
    string name_;

   public:
    VariableExprAST(const string& name) : name_(name) {}
};
