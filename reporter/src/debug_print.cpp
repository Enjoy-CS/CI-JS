#include "debug_print.h"

namespace lox::reporter {

void printDebug(const std::string &str) {
#ifdef LOX_DEBUG_MODE
    std::cout << str << std::endl;
#endif 
}

} 