#ifndef __EXPR_AST_H__
#define __EXPR_AST_H__

#include <string>

using namespace std;

// Base class for all expression nodes
class ExprAST {
   public:
    virtual ~ExprAST() = default;
    // virtual ~ExprAST() {}

    virtual string toString();
};

#endif  // !__EXPR_AST_H__
