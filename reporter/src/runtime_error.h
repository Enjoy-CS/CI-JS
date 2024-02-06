#ifndef __LOX_REPORTER_RUNTIME_ERROR_H__
#define __LOX_REPORTER_RUNTIME_ERROR_H__

#include "error_reporter.h"
#include "token.h"

#include <exception>
#include <stdexcept>

namespace lox::reporter {

using types::Token;
class RuntimeError : std::exception {};
auto reportRuntimeError(ErrReporter& reporter, const Token& token, const std::string& message) -> RuntimeError;

}
#endif // __LOX_REPORTER_RUNTIME_ERROR_H__