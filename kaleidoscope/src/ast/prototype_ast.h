#pragma once

#include <string>
#include <vector>

#include "llvm/IR/Function.h"

using namespace std;
using namespace llvm;

// Class for representing function prototypes
class PrototypeAST {
    string name_;
    vector<string> args_;

   public:
    PrototypeAST(const string& name, vector<string> args)
        : name_(name), args_(std::move(args)) {}

    auto getName() -> const string& { return name_; }

    auto codegen() -> Function*;
};
