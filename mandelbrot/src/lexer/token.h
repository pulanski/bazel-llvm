
#pragma once

#include <string>

using namespace std;

class Token {
   public:
    enum class Kind {
        Number,
        Identifier,
        LeftParen,
        RightParen,
        LeftSquare,
        RightSquare,
        LeftCurly,
        RightCurly,
        LessThan,
        GreaterThan,
        Equal,
        Plus,
        Minus,
        Asterisk,
        Slash,
        Hash,
        Dot,
        Comma,
        Colon,
        Semicolon,
        SingleQuote,
        DoubleQuote,
        Comment,
        Pipe,
        EndOfFile,
        Unexpected,
    };

    Token(Kind kind) noexcept : token_kind_(kind) {}

    Token(Kind kind, const char* beg, std::size_t len) noexcept
        : token_kind_(kind), token_lexeme_(beg, len) {}

    Token(Kind kind, const char* beg, const char* end) noexcept
        : token_kind_(kind), token_lexeme_(beg, std::distance(beg, end)) {}

    Kind kind() const noexcept { return token_kind_; }

    void kind(Kind kind) noexcept { token_kind_ = kind; }

    bool is(Kind kind) const noexcept { return token_kind_ == kind; }

    bool isNot(Kind kind) const noexcept { return token_kind_ != kind; }

    bool isOneOf(Kind k1, Kind k2) const noexcept { return is(k1) || is(k2); }

    template <typename... Ts>
    bool isOneOf(Kind k1, Kind k2, Ts... ks) const noexcept {
        return is(k1) || is_one_of(k2, ks...);
    }

    string_view lexeme() const noexcept { return token_lexeme_; }

    void lexeme(string_view lexeme) noexcept {
        token_lexeme_ = std::move(lexeme);
    }

   private:
    Kind token_kind_;
    string_view token_lexeme_;
};
