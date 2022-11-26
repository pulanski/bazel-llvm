#include "lexer.h"

#include <gtest/gtest.h>

#include "token.h"

TEST(Lexer, Identifier) {
    Lexer lexer("abc");
    Token token = lexer.next();
    EXPECT_EQ(token.kind(), Token::Kind::Identifier);
    EXPECT_EQ(token.lexeme(), "abc");
}

TEST(Lexer, Number) {
    Lexer lexer("123");
    Token token = lexer.next();
    EXPECT_EQ(token.kind(), Token::Kind::Number);
    EXPECT_EQ(token.lexeme(), "123");
}
