#ifndef __LOX_SCANNER_H__
#define __LOX_SCANNER_H__

#include "error_reporter.h"
#include "token.h"

#include <list>
#include <vector>

namespace lox {

using reporter::ErrReporter;
using types::Token;
using types::TokenType;
using TokenVec = std::vector<Token>;

class Scanner {
public:
    Scanner(const std::string& source, ErrReporter& reporter);
    auto tokenize() -> TokenVec;

private:
    auto isAtEnd() const -> bool;
    void tokenizeOne();
    void advance();
    auto matchNext(char expected) -> bool;
    auto peek() -> char;
    auto peekNext() -> char;
    void skipComment();
    void skipBlockComment();
    void consumeIdentifier();
    void consumeNumber();
    void consumeString();
    void addToken(TokenType tt);

    const std::string& source_;
    ErrReporter& reporter_;
    std::list<Token> tokens_;
    size_t start_ {0};
    size_t current_ {0};
    uint16_t line_ {1};
};

}

#endif // __LOX_SCANNER_H__