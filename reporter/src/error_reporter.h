#ifndef __LOX_REPORTER_ERROR_H__
#define __LOX_REPORTER_ERROR_H__

#include <string>
#include <vector>

namespace lox::reporter {

enum class LoxStatus {
    OK,
    ERROR,
};

class ErrReporter {
public:
    void clean();
    void print();
    auto getStatus() const -> LoxStatus;
    void setErrStatus(uint32_t line_number, const std::string& err_message);

private:
    std::vector<std::string> err_storage;
    LoxStatus status {LoxStatus::OK};
};

}

#endif // __LOX_REPORTER_ERROR_H__