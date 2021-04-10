#pragma once

#include <exception>

#define CHECK_RANGE_OR_ERROR(expression) \
if (!(expression)) { throw std::range_error("Out of range: " #expression);}