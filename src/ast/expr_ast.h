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

// TODO maybe implement
// std::unique_ptr<ExprAST> LogError(const char *Str) {
//   fprintf(stderr, "LogError: %s\n", Str);
//   return nullptr;
// }
// std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
//   LogError(Str);
//   return nullptr;
// }
