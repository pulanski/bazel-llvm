#include "lexer.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <regex>

#include "token.h"

// CurTok is the current token the parser is looking at.
int curTok;
string identifierStr;
double numVal;

int getTok() {
    static int lastChar = ' ';

    // The first thing we need to do is ignore whitespace between tokens
    while (isspace((lastChar))) {
        lastChar = getchar();
    }

    // Next thing is recognize identifiers and keywords
    if (isalpha(lastChar)) {
        identifierStr = lastChar;

        // Stacking together all alphanumeric characters into IdentifierStr
        while (isalnum(lastChar = getchar())) {
            identifierStr += lastChar;
        }

        if (identifierStr == "def") {
            return TokDef;
        }

        if (identifierStr == "extern") {
            return TokExtern;
        }

        return TokIdentifier;
    }

    // Stacking together only numeric values
    if (isdigit(lastChar) || lastChar == '.') {
        string numStr;

        do {
            numStr += lastChar;
            lastChar = getchar();
        } while (isdigit(lastChar) || lastChar == '.');

        // convert numeric string into numeric values
        // and store in NumVal
        numVal = strtod(numStr.c_str(), nullptr);
        return TokNumber;
    }

    // Handling comments by skipping to the end of the line and
    // returning the next token
    if (lastChar == '#') {
        do {
            lastChar = getchar();
        } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

        if (lastChar != EOF) {
            return getTok();
        }
    }

    // Finally, if the input doesn't match one of the above cases
    // it's either an operator character like '+' or the end of the file
    if (lastChar == EOF) {
        return TokEof;
    }

    // Otherwise, just return the character as its ascii value.
    int thisChar = lastChar;
    lastChar = getchar();
    return thisChar;
}

/// CurTok/getNextToken - Provide a simple token buffer.
/// getNextToken reads another token from the
/// lexer and updates CurTok with its results.
int getNextToken() { return curTok = getTok(); }

// regex binary_digit("[0-1]");
// regex octal_digit("[0-7]");
// regex decimal_digit("[0-9]");
