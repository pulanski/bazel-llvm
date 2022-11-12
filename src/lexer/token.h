#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>

using namespace std;

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
    TokEof = -1,

    // commands
    TokDef = -2,
    TokExtern = -3,

    // primary
    TokIdentifier = -4,
    TokNumber = -5,
};

extern string identifierStr;  // Filled in if tok_identifier
extern double numVal;         // Filled in if tok_number

#endif  // !__TOKEN_H__
