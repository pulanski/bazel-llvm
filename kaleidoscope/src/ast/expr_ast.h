#pragma once

#include <string>

#include "llvm/IR/Value.h"

using namespace std;
using namespace llvm;

// Base class for all expression nodes
class ExprAST {
   public:
    virtual ~ExprAST() = default;

    virtual Value* codegen() = 0;

    // virtual string toString();
};
