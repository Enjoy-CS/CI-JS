#include "scanner.h"

#include <map>
// #include <string_view>

namespace lox {

using reporter::ErrReporter;
using types::Literal;
using types::LiteralOptional;
using types::Token;
using types::TokenType;

namespace {

auto isAlpha(char c) -> bool {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

auto isDigit(char c) -> bool { return c >= '0' && c <= '9'; }
auto isAlphaNumeric(char c) -> bool { return isAlpha(c) || isDigit(c); }
auto findIdentifier(const std::string& str) -> TokenType {
    static const std::map<std::string, TokenType> lookup_table {
        {"and", TokenType::AND},       {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},     {"false", TokenType::LOX_FALSE},
        {"fun", TokenType::FUN},       {"for", TokenType::FOR},
        {"if", TokenType::IF},         {"nil", TokenType::NIL},
        {"or", TokenType::OR},         {"print", TokenType::PRINT},
        {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
        {"this", TokenType::THIS},     {"true", TokenType::LOX_TRUE},
        {"var", TokenType::VAR},       {"while", TokenType::WHILE}};

    auto iter = lookup_table.find(str);
    if (iter == lookup_table.end()) return TokenType::IDENTIFIER;
    return iter->second;
}
auto getLexeme(const std::string& source, size_t start, size_t end) -> std::string {
    return source.substr(start, end);
}
auto createOptionalLiteral(TokenType t, const std::string& lexeme) -> LiteralOptional {
    switch (t) {
    case TokenType::NUMBER:
        return types::createOptionalLiteral(std::stod(lexeme));
    case TokenType::STRING:
        return types::createOptionalLiteral(lexeme.substr(1, lexeme.size() - 2));
    default:
        return std::nullopt;
    }
}

} // anonymous namespace

Scanner::Scanner(const std::string& source, ErrReporter& reporter)
: source_{source}, reporter_{reporter} {}

void Scanner::addToken(TokenType t) {
    const std::string lexeme {getLexeme(source_, start_, current_ - start_)};
    tokens_.emplace_back(t, lexeme, createOptionalLiteral(t, lexeme), line_);
}

inline void Scanner::advance() { ++current_; }
void Scanner::skipBlockComment() {
    int nesting = 1;
    while (nesting > 0) {
        if (peek() == '\0') {
            reporter_.setErrStatus(line_, "Block comment is not closed");
            return;
        }

        if (peek() == '/' && peekNext() == '*') {
            advance();
            ++nesting;
        } else if(peek() == '*' && peekNext() == '/') {
            advance();
            --nesting;
        } else if (peek() == '\n') {
            ++line_;
        }

        advance();
    }
}

void Scanner::skipComment() {
    while (!isAtEnd() && peek() != '\n') { advance(); }
}

void Scanner::consumeIdentifier() {
    while (isAlphaNumeric(peek())) advance();
}

void Scanner::consumeNumber() {
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) advance();
    }
}

//TODO consumeString 구현해야 함.

} // lox namespace
