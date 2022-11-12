#pragma once

#include <string>

using namespace std;

// Base class for all expression nodes
class ExprAST {
   public:
    virtual ~ExprAST() = default;
    // virtual ~ExprAST() {}

    // virtual string toString();
};
