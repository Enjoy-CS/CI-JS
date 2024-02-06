#include "literal.h"

namespace lox::types {

auto getLiteralString(const Literal& value) -> std::string {
    switch (value.index()) {
        case 0: // string
            return std::get<0>(value);
        case 1: { // double
            std::string result {std::to_string(std::get<1>(value))};
            auto pos {result.find(".000000")};
            if (pos != std::string::npos) {
                result.erase(pos, std::string::npos);
            } else {
                // First, find the position of the decimal point to ensure we don't erase zeros from an integer part.
                auto decimal_pos = result.find('.');
                if (decimal_pos != std::string::npos) {
                    // Erase trailing zeros after the last non-zero digit after the decimal point.
                    auto last_non_zero = result.find_last_not_of('0');
                    if (last_non_zero != std::string::npos && last_non_zero > decimal_pos) {
                        result.erase(last_non_zero + 1);
                    }
                    // If the string ends with a decimal point after erasing zeros, remove it as well.
                    if (result.back() == '.') {
                        result.pop_back();
                    }
                }
            }
            return result;
        }
        default: 
            static_assert(2 == std::variant_size_v<Literal>, "Looks like you forgot to update the case in getLiteralString()");
            return "";
    }
}

auto createOptionalLiteral(double d_val) -> LiteralOptional {
    return LiteralOptional {std::in_place, d_val};
}

auto createOptionalLiteral(const std::string& lexeme) -> LiteralOptional {
    return LiteralOptional {std::in_place, lexeme};
}

}