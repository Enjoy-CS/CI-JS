#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "literal.h"

namespace lox::types {

enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COLON,
    COMMA,
    DOT,
    QUESTION,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    MINUS,
    MINUS_MINUS,
    PLUS,
    PLUS_PLUS,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    LOX_FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    LOX_TRUE,
    VAR,
    WHILE,

    LOX_EOF
};

class Token {
public:
    Token(TokenType type, std::string lexeme, LiteralOptional literal, uint16_t line);
    Token(TokenType type, std::string_view lexeme, LiteralOptional literal, uint16_t line);
    Token(TokenType type, std::string_view lexeme);

    auto toString() const -> std::string;
    auto getType() const -> TokenType;
    auto getTypeString() const -> std::string;
    auto getLine() const -> uint16_t;
    auto getLexeme() const -> std::string;
    auto getLiteralOptional() const -> LiteralOptional;

private:
    const TokenType type_;
    const std::string lexeme_;
    LiteralOptional literal_ {std::nullopt};
    const int line_ {-1};
};

}
#endif // __TOKEN_H__