#pragma once

#include "TCString.h"

#define THROW_ERROR_CAPTION(caption, ex) \
{ throw std::runtime_error(Tce::String::Format(#caption ":\n%s", ex.what()).Data());}

#define THROW_RUNTIME_ERROR(...) \
{ throw std::runtime_error(Tce::String::Format(__VA_ARGS__).Data());}

#define CHECK_RUNTIME_OR_ERROR(expression, ...) \
if (!(expression)) { throw std::runtime_error(Tce::String::Format(__VA_ARGS__).Data());}

#define CHECK_RANGE_OR_ERROR(expression) \
if (!(expression)) { throw std::range_error("Out of Range Exception: " #expression);}

#define CHECK_ARGUMENT_OR_ERROR(arg, expression) \
if (!(expression)) { throw std::range_error("Argument \"" #arg "\" Exception: " #expression);}