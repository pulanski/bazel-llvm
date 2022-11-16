#pragma once

#include <string>

using namespace std;

/// The lexer returns tokens [0-255] if it is an unknown character, otherwise
/// one of these for known things.
enum Token {
    /// End of file token.
    TokEof = -1,

    /// "def" token.
    TokDef = -2,

    /// "extern" token.
    TokExtern = -3,

    // Identifier token (e.g. "foo").
    TokIdentifier = -4,

    // Number token (e.g. "1.0").
    TokNumber = -5,
};

// Filled in if tok_identifier
extern string identifierStr;

// Filled in if tok_number
extern double numVal;
