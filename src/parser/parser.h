#pragma once

#include <map>
#include <memory>

#include "../ast/binary_expr_ast.h"
#include "../ast/call_expr_ast.h"
#include "../ast/expr_ast.h"
#include "../ast/function_ast.h"
#include "../ast/number_expr_ast.h"
#include "../ast/prototype_ast.h"
#include "../ast/variable_expr_ast.h"
#include "../lexer/lexer.h"
#include "../lexer/token.h"

using namespace std;

extern map<char, int> binOpPrecedence;
extern int getTokenPrecedence();

// Parsing routines
unique_ptr<ExprAST> parseNumberExpr();
unique_ptr<ExprAST> parseParenExpr();
unique_ptr<ExprAST> parseIdentifierExpr();
unique_ptr<ExprAST> parsePrimary();
unique_ptr<ExprAST> parseExpression();
unique_ptr<ExprAST> parseBinOpRHS(int expr_precedence, unique_ptr<ExprAST> lhs);
unique_ptr<PrototypeAST> parsePrototype();
unique_ptr<FunctionAST> parseDefinition();
unique_ptr<FunctionAST> parseTopLevelExpr();
unique_ptr<PrototypeAST> parseExtern();

// Top-level parsing routines (used within driver)
void handleDefinition();
void handleExtern();
void handleTopLevelExpression();
