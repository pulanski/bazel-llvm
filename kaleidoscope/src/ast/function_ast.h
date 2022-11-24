#pragma once

#include <memory>

#include "expr_ast.h"
#include "prototype_ast.h"

// Class for representing function definitions
class FunctionAST {
    unique_ptr<PrototypeAST> proto_;
    unique_ptr<ExprAST> body_;

   public:
    FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<ExprAST> block)
        : proto_(std::move(proto)), body_(std::move(block)) {}

    Function* codegen();
};
