#pragma once

#include "fundamental.hpp"

// Remove params
#define RCOM_EAT(...)

// Seperate params
#define RCOM_EXPAND(...) __VA_ARGS__

// Combine params
#define RCOM_CONCAT_IMP(a, b) a ## b
#define RCOM_CONCAT(a, b) RCOM_CONCAT_IMP(a, b)

// Make into string
#define RCOM_STRINGIFY(x) #x
#define RCOM_XSTRINGIFY(x) RCOM_STRINGIFY(x)

// Location as a string
#define RCOM_CODE_LOCATION "FILE: " __FILE__ " Line: " RCOM_XSTRINGIFY(__LINE__)
