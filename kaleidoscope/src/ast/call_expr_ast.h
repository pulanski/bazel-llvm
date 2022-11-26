#pragma once

#include <memory>
#include <string>
#include <vector>

#include "expr_ast.h"
#include "kaleidoscope/src/globals/globals.h"
#include "kaleidoscope/src/logger/logger.h"
#include "llvm/IR/IRBuilder.h"

// Expression class for function calls
class CallExprAST : public ExprAST {
    string callee_;
    vector<unique_ptr<ExprAST>> args_;

   public:
    CallExprAST(string_view callee, vector<unique_ptr<ExprAST>> args)
        : callee_(callee), args_(std::move(args)) {}

    Value* codegen() override;
};
