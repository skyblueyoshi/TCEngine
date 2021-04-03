#include "StringHelper.h"

std::string StringHelper::MakeFormat(const char * format, ...) {
    va_list args;
    va_start(args, format);
    std::string result = MakeFormatFromList(format, args);
    va_end(args);
    return result;
}

std::string StringHelper::MakeFormatFromList(const char * format, va_list list) {
    int size = vsnprintf(nullptr, 0, format, list);
    std::string formatted;
    if (size > 0) {
        formatted.resize(size);
        vsnprintf(&formatted[0], size + 1, format, list);
    }
    return formatted;
}