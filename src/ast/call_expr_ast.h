#pragma once

#include <memory>
#include <string>
#include <vector>

#include "expr_ast.h"
#include "llvm/IR/IRBuilder.h"
#include "src/kaleidoscope/kaleidoscope.h"
#include "src/logger/logger.h"

// Expression class for function calls
class CallExprAST : public ExprAST {
    string callee_;
    vector<unique_ptr<ExprAST>> args_;

   public:
    CallExprAST(const string& callee, vector<unique_ptr<ExprAST>> args)
        : callee_(callee), args_(std::move(args)) {}

    auto codegen() -> Value* override;
};
