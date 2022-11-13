#pragma once

#include <string>

#include "llvm/IR/Value.h"

using namespace std;

// Base class for all expression nodes
class ExprAST {
   public:
    virtual ~ExprAST() = default;

    virtual llvm::Value* codegen() = 0;

    // virtual string toString();
};
