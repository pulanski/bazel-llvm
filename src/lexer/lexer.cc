#include "lexer.h"

#include <cstdio>
#include <cstdlib>
#include <regex>

#include "token.h"

using namespace std;

// CurTok is the current token the parser is looking at.
int CurTok;
string IdentifierStr;
double NumVal;

int gettok() {
    static int LastChar = ' ';

    // The first thing we need to do is ignore whitespace between tokens
    while (isspace((LastChar))) {
        LastChar = getchar();
    }

    // Next thing is recognize identifiers and keywords
    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;

        // Stacking together all alphanumeric characters into IdentifierStr
        while (isalnum(LastChar = getchar())) {
            IdentifierStr += LastChar;
        }

        if (IdentifierStr == "def") {
            return TokDef;
        }

        if (IdentifierStr == "extern") {
            return TokExtern;
        }

        return TokIdentifier;
    }

    // Stacking together only numeric values
    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;

        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        // convert numeric string into numeric values
        // and store in NumVal
        NumVal = strtod(NumStr.c_str(), nullptr);
        return TokNumber;
    }

    // Handling comments by skipping to the end of the line and
    // returning the next token
    if (LastChar == '#') {
        do {
            LastChar = getchar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF) {
            return gettok();
        }
    }

    // Finally, if the input doesn't match one of the above cases
    // it's either an operator character like '+' or the end of the file
    if (LastChar == EOF) {
        return TokEof;
    }

    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;

    return 0;
}

/// CurTok/getNextToken - Provide a simple token buffer.
/// getNextToken reads another token from the
/// lexer and updates CurTok with its results.
int getNextToken() { return CurTok = gettok(); }

// regex binary_digit("[0-1]");
// regex octal_digit("[0-7]");
// regex decimal_digit("[0-9]");
