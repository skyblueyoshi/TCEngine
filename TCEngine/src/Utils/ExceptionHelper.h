#pragma once

#include <exception>

#define CHECK_RANGE_OR_ERROR(expression) \
if (!(expression)) { throw std::range_error("Out of Range Exception: " #expression);}

#define CHECK_ARGUMENT_OR_ERROR(arg, expression) \
if (!(expression)) { throw std::range_error("Argument \"" #arg "\" Exception: " #expression);}