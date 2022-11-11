#pragma once

#include <memory>

#include "PrototypeAST.h"

using namespace std;

// Class for representing function definitions
class FunctionAST {
    unique_ptr<PrototypeAST> proto_;
    unique_ptr<ExprAST> block_;

   public:
    FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<ExprAST> block)
        : proto_(std::move(proto)), block_(std::move(block)) {}
};
