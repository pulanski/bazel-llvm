#include "parser.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../logger/logger.h"

using namespace std;

map<char, int> binOpPrecedence;

int getTokenPrecedence() {
    if (!isascii(curTok)) {
        return -1;
    }

    // Make sure it's a declared binop.
    int tokPrec = binOpPrecedence[curTok];
    if (tokPrec <= 0) {
        return -1;
    }

    return tokPrec;
}

/// numberexpr ::= number
unique_ptr<ExprAST> parseNumberExpr() {
    auto number = make_unique<NumberExprAST>(numVal);
    getNextToken();  // consume the number
    return std::move(number);
}

/// parenexpr ::= '(' expression ')'
unique_ptr<ExprAST> parseParenExpr() {
    getNextToken();  // skip `(`
    auto expr = parseExpression();
    if (!expr) {
        return nullptr;
    }

    if (curTok != ')') {
        return logSyntaxError("Expected `)`, but found token " +
                              to_string(curTok));
    }

    getNextToken();  // skip `)`
    return expr;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
unique_ptr<ExprAST> parseIdentifierExpr() {
    string idName = identifierStr;

    getNextToken();  // eat the identifier

    if (curTok != '(') {  // simple variable ref
        return make_unique<VariableExprAST>(idName);
    }

    // call
    getNextToken();  // eat `(`
    vector<unique_ptr<ExprAST>> args;

    if (curTok != ')') {
        while (true) {
            if (auto arg = parseExpression()) {
                args.push_back(std::move(arg));
            } else {
                return nullptr;
            }

            if (curTok == ')') {
                break;
            }

            if (curTok != ',') {
                return logSyntaxError(
                    "Expected `)` or `,` in argument list, but found token, `" +
                    to_string(curTok) + "`.");
            }

            getNextToken();  // eat the `,`
        }
    }

    getNextToken();  // Eat the `)`

    return make_unique<CallExprAST>(idName, std::move(args));
}

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
unique_ptr<ExprAST> parsePrimary() {
    switch (curTok) {
        default:
            return logSyntaxError(
                "Expected an expression, but found unknown token `" +
                to_string(curTok) + "`.");
        case TokIdentifier:
            return parseIdentifierExpr();
        case TokNumber:
            return parseNumberExpr();
        case '(':
            return parseParenExpr();
    }
}

/// binoprhs
///   ::= ('+' primary)*
unique_ptr<ExprAST> parseBinOpRHS(int expr_precedence,
                                  unique_ptr<ExprAST> lhs) {
    // If this is a binop, find its precedence.
    while (true) {
        int tokenPrecedence = getTokenPrecedence();

        // If this is a binop that binds at least as tightly as the current
        // binop,
        // consume it, otherwise we are done.
        if (tokenPrecedence < expr_precedence) {
            return lhs;
        }

        // Okay, we know this is a binOp
        int binOp = curTok;
        getNextToken();  // eat the binOp

        // Parse the primary expression after the binary operator.
        auto rhs = parsePrimary();
        if (!rhs) {
            return nullptr;
        }

        // If BinOp binds less tightly with RHS than the operator after RHS, let
        // the pending operator take RHS as its LHS.
        int nextPrecedence = getTokenPrecedence();
        if (tokenPrecedence < nextPrecedence) {
            rhs = parseBinOpRHS(tokenPrecedence + 1, std::move(rhs));
            if (!rhs) {
                return nullptr;
            }
        }

        // merge the LHS and RHS
        lhs = make_unique<BinaryExprAST>(binOp, std::move(lhs), std::move(rhs));
    }
}

/// expression
///   ::= primary binoprhs
unique_ptr<ExprAST> parseExpression() {
    auto lhs = parsePrimary();

    if (!lhs) {
        return nullptr;
    }

    return parseBinOpRHS(0, std::move(lhs));
}

/// prototype
///   ::= id '(' id* ')'
unique_ptr<PrototypeAST> parsePrototype() {
    if (curTok != TokIdentifier) {
        logPrototypeSyntaxError(
            "Expected function name in prototype, but instead found token, `" +
            to_string(curTok) + "`.");
    }

    string fnName = identifierStr;
    getNextToken();

    if (curTok != '(') {
        return logPrototypeSyntaxError(
            "Expected '(' in prototype, but instead found token, `" +
            to_string(curTok) + "`.");
    }

    vector<string> argNames;

    while (getNextToken() == TokIdentifier) {
        argNames.push_back(identifierStr);
    }

    getNextToken();  // eat `)`.

    return make_unique<PrototypeAST>(fnName, argNames);
}

/// definition ::= 'def' prototype expression
unique_ptr<FunctionAST> parseDefinition() {
    getNextToken();  // eat `def`

    auto proto = parsePrototype();
    if (!proto) {
        return nullptr;
    }

    if (auto expr = parseExpression()) {
        return make_unique<FunctionAST>(std::move(proto), std::move(expr));
    }

    return nullptr;
}

/// toplevelexpr ::= expression
unique_ptr<FunctionAST> parseTopLevelExpr() {
    if (auto expr = parseExpression()) {
        // Make an anonymous proto.
        auto proto = make_unique<PrototypeAST>("__anon_expr", vector<string>());

        return make_unique<FunctionAST>(std::move(proto), std::move(expr));
    }
    return nullptr;
}

/// external ::= 'extern' prototype
unique_ptr<PrototypeAST> parseExtern() {
    getNextToken();  // eat `extern`

    return parsePrototype();
}

///////////////////////
// Top-level Parsing //
///////////////////////

void handleDefinition() {
    if (parseDefinition()) {
        logInfo("Successfully parsed a function definition.");
    } else {
        // Skip the token for error recovery
        getNextToken();
    }
}

void handleExtern() {
    if (parseExtern()) {
        logInfo("Successfully parsed an extern.");
    } else {
        // Skip the token for error recovery
        getNextToken();
    }
}

void handleTopLevelExpression() {
    // Evaluate a top-level expression into an anonymous function.
    if (parseTopLevelExpr()) {
        logInfo("Successfully parsed a top level expression.");
    } else {
        // Skip the token for error recovery
        getNextToken();
    }
}
