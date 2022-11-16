#pragma once

#include <map>
#include <memory>

#include "src/ast/binary_expr_ast.h"
#include "src/ast/call_expr_ast.h"
#include "src/ast/expr_ast.h"
#include "src/ast/function_ast.h"
#include "src/ast/number_expr_ast.h"
#include "src/ast/prototype_ast.h"
#include "src/ast/variable_expr_ast.h"
#include "src/lexer/lexer.h"
#include "src/lexer/token.h"

using namespace std;

extern map<char, int> binOpPrecedence;
extern int getTokenPrecedence();

// Parsing routines

/// Parsing routine for number expressions.
/// numberexpr ::= number
unique_ptr<ExprAST> parseNumberExpr();

/// Parsing routine for parenthesized expressions.
/// parenexpr ::= '(' expression ')'
unique_ptr<ExprAST> parseParenExpr();

/// Parsing routine for identifier expressions.
/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
unique_ptr<ExprAST> parseIdentifierExpr();

/// Parsing routine for primary expressions.
/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
unique_ptr<ExprAST> parsePrimary();

/// binoprhs
///   ::= ('+' primary)*
unique_ptr<ExprAST> parseBinOpRHS(int expr_precedence, unique_ptr<ExprAST> lhs);

/// Parsing routine for expressions
/// expression
///   ::= primary binoprhs
unique_ptr<ExprAST> parseExpression();

unique_ptr<PrototypeAST> parsePrototype();
unique_ptr<FunctionAST> parseDefinition();
unique_ptr<FunctionAST> parseTopLevelExpr();
unique_ptr<PrototypeAST> parseExtern();

// Top-level parsing routines (used within driver)

void handleDefinition();
void handleExtern();
void handleTopLevelExpression();
