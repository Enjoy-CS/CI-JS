#include "error_reporter.h"

#include <iostream>

namespace lox::reporter {

void ErrReporter::clean() {
    err_storage.clear();
    status = LoxStatus::OK;
}

void ErrReporter::print() {
    for (auto &err : err_storage) {
        std::cerr << err << std::endl;
    }
}

auto ErrReporter::getStatus() const -> LoxStatus { return status; }
void ErrReporter::setErrStatus(uint32_t line_number, const std::string &err_message) {
    err_storage.emplace_back("Line Number: " + std::to_string(line_number) \
    + ", Error: " + err_message);
    status = LoxStatus::ERROR;
}

}