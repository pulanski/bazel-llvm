#pragma once

#include <cstdlib>
#include <string>

using namespace std;

/// A buffer containing the current token the lexer is looking at.
extern int curTok;

/// Returns the token within the buffer.
int gettok();

/// Advances the lexer to the next token and returns it.
int getNextToken();

extern string identifierStr;
extern double numVal;
