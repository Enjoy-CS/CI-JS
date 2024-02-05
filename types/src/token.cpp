#include "token.h"
#include "literal.h"

#include <map>
#include <type_traits>
#include <utility>

namespace lox::types {

static auto tokenTypeToStr(const TokenType &value) -> std::string {
    static const std::map<TokenType, std::string> lookup_table {
        {TokenType::LEFT_PAREN, "LEFT_PAREN"},
        {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
        {TokenType::LEFT_BRACE, "LEFT_BRACE"},
        {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
        {TokenType::COMMA, "COMMA"},
        {TokenType::COLON, "COLON"},
        {TokenType::DOT, "DOT"},
        {TokenType::QUESTION, "QUESTION"},
        {TokenType::SEMICOLON, "SEMICOLON"},
        {TokenType::SLASH, "SLASH"},
        {TokenType::STAR, "STAR"},
        {TokenType::BANG, "BANG"},
        {TokenType::BANG_EQUAL, "BANG_EQUAL"},
        {TokenType::EQUAL, "EQUAL"},
        {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
        {TokenType::GREATER, "GREATER"},
        {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
        {TokenType::LESS, "LESS"},
        {TokenType::LESS_EQUAL, "LESS_EQUAL"},
        {TokenType::MINUS, "MINUS"},
        {TokenType::MINUS_MINUS, "MINUS_MINUS"},
        {TokenType::PLUS, "PLUS"},
        {TokenType::PLUS_PLUS, "PLUS_PLUS"},
        {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::STRING, "STRING"},
        {TokenType::NUMBER, "NUMBER"},
        {TokenType::AND, "AND"},
        {TokenType::CLASS, "CLASS"},
        {TokenType::ELSE, "ELSE"},
        {TokenType::LOX_FALSE, "FALSE"},
        {TokenType::FUN, "FUN"},
        {TokenType::FOR, "FOR"},
        {TokenType::IF, "IF"},
        {TokenType::NIL, "NIL"},
        {TokenType::OR, "OR"},
        {TokenType::PRINT, "PRINT"},
        {TokenType::RETURN, "RETURN"},
        {TokenType::SUPER, "SUPER"},
        {TokenType::THIS, "THIS"},
        {TokenType::LOX_TRUE, "TRUE"},
        {TokenType::VAR, "VAR"},
        {TokenType::WHILE, "WHILE"},
        {TokenType::LOX_EOF, "EOF"}
    };
    return lookup_table.find(value)->second;
}

Token::Token(TokenType type, std::string lexeme, LiteralOptional literal, uint16_t line)
: type_(type), lexeme_(std::move(lexeme)), literal_(std::move(literal)), line_(line) {}

Token::Token(TokenType type, const char *lexeme, LiteralOptional literal, uint16_t line)
: type_(type), lexeme_(lexeme), literal_(std::move(literal)), line_(line) {}

Token::Token(TokenType type, const char *lexeme)
: type_(type), lexeme_(lexeme) {}

auto Token::toString() const -> std::string {
    std::string result = std::to_string(line_) + " " + tokenTypeToStr(type_) + " " + lexeme_ + " ";
    result += literal_.has_value() ? getLiteralString(literal_.value()) : "No Literal";
    return result;
}

auto Token::getType() const -> TokenType { return type_; }
auto Token::getTypeString() const -> std::string { return tokenTypeToStr(type_); }
auto Token::getLine() const -> uint16_t { return line_; }
auto Token::getLexeme() const -> std::string { return lexeme_; }
auto Token::getLiteralOptional() const -> LiteralOptional { return literal_; }

}