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

void Scanner::consumeString() {
    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\n') ++line_;
        advance();
    }

    if (isAtEnd()) {
        reporter_.setErrStatus(line_, "Unterminated String");
    } else {
        advance(); // consume the closing quote '"'
    }
}

auto Scanner::isAtEnd() const -> bool { return current_ >= source_.size(); }
auto Scanner::matchNext(char expected) -> bool {
    bool next_matches = (peek() == expected);
    if (next_matches) advance();
    return next_matches;
}

auto Scanner::peek() -> char {
    if (isAtEnd()) return '\0';
    return source_[current_];
}

auto Scanner::peekNext() -> char {
    if ((current_ + 1) >= source_.size()) return '\0';
    return source_[current_ + 1];
}

void Scanner::tokenizeOne() {
    char c = peek();
    advance();
    switch(c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case ':': addToken(TokenType::COLON); break;
        case '.': addToken(TokenType::DOT); break;
        case '?': addToken(TokenType::QUESTION); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '!':
            addToken(matchNext('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(matchNext('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '>':
            addToken(matchNext('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '<':
            addToken(matchNext('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '-':
            addToken(matchNext('-') ? TokenType::MINUS_MINUS : TokenType::MINUS);
            break;
        case '+':
            addToken(matchNext('+') ? TokenType::PLUS_PLUS : TokenType::PLUS);
            break;
        case '/':
            if (matchNext('/'))
                skipComment();
            else if (matchNext('*'))
                skipBlockComment();
            else
                addToken(TokenType::SLASH);
            break;
        case ' ':
        case '\t':
        case '\r': break;  // whitespace
        case '\n': ++line_; break;
        case '"':
            consumeString();
            addToken(TokenType::STRING);
            break;
        default:
            if (isDigit(c)) {
                consumeNumber();
                addToken(TokenType::NUMBER);
            } else if (isAlpha(c)) {
                consumeIdentifier();
                const std::string identifier {getLexeme(source_, start_, current_ - start_)};
                addToken(findIdentifier(identifier));
            } else {
                std::string message = "Unexpected character: ";
                message.append(1, static_cast<char>(c));
                reporter_.setErrStatus(line_, message);
            }
            break;
    }
}

} // lox namespace
