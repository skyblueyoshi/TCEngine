#pragma once

#include <string>
#include <stdarg.h>

class StringHelper {
public:
    static std::string MakeFormat(const char * format, ...);
    static std::string MakeFormatFromList(const char * format, va_list list);
};
