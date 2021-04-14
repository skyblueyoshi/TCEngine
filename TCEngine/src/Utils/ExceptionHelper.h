#pragma once

#include <exception>
#include "StringHelper.h"

#define CHECK_RUNTIME_OR_ERROR(expression, ...) \
if (!(expression)) { throw std::runtime_error(StringHelper::MakeFormat(__VA_ARGS__));}

#define CHECK_RANGE_OR_ERROR(expression) \
if (!(expression)) { throw std::range_error("Out of Range Exception: " #expression);}

#define CHECK_ARGUMENT_OR_ERROR(arg, expression) \
if (!(expression)) { throw std::range_error("Argument \"" #arg "\" Exception: " #expression);}