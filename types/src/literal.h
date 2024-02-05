#ifndef __LITERAL_H__
#define __LITERAL_H__

#include <optional>
#include <variant>
#include <string>

namespace lox::types {

using Literal = std::variant<std::string, double>;
using LiteralOptional = std::optional<Literal>;

auto getLiteralString(const Literal &value) -> std::string;
auto createOptionalLiteral(double d_val) -> LiteralOptional;
auto createOptionalLiteral(const std::string &lexeme) -> LiteralOptional;

}
#endif // __LITERAL_H__