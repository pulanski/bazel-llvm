#pragma once

#include <string>

#include "expr_ast.h"
#include "src/kaleidoscope/kaleidoscope.h"
#include "src/logger/logger.h"

// Expression class for referencing a variable
class VariableExprAST : public ExprAST {
    string name_;

   public:
    VariableExprAST(const string& name) : name_(name) {}
    Value* codegen() override;
};
