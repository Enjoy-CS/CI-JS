#include "runtime_error.h"

namespace lox::reporter {

auto reportRuntimeError(ErrReporter& reporter, const Token& token, const std::string& message) -> RuntimeError {
    reporter.setErrStatus(token.getLine(), token.getLexeme() + ": " + message);
    return RuntimeError{};
}

}