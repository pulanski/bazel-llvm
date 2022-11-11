#pragma once

#include <string>
#include <vector>

#include "ExprAST.h"

using namespace std;

// Class for representing function prototypes
class PrototypeAST {
    string name_;
    vector<string> args_;

   public:
    PrototypeAST(const string& name, vector<string> args)
        : name_(name), args_(std::move(args)) {}

    const string& getName() { return name_; }
};
