#ifndef __LEXER_H__
#define __LEXER_H__

#include <cstdlib>
#include <string>

using namespace std;

extern int curTok;
int gettok();
int getNextToken();

extern string identifierStr;
extern double numVal;

#endif  // !__LEXER_H__
