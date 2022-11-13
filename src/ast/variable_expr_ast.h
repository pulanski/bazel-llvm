#pragma once

#include <string>

#include "../kaleidoscope/kaleidoscope.h"
#include "../logger/logger.h"
#include "expr_ast.h"

using namespace std;

// Expression class for referencing a variable
class VariableExprAST : public ExprAST {
    string name_;

   public:
    VariableExprAST(const string& name) : name_(name) {}
    llvm::Value* codegen() override;
};
