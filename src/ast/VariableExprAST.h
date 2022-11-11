#pragma once

#include <string>

#include "ExprAST.h"

using namespace std;

// Expression class for referencing a variable
class VariableExprAST : ExprAST {
    string name_;

   public:
    VariableExprAST(const string& name) : name_(name) {}
};
