#pragma once

#include <cstring>
#include <cstdint>

// Remove params
#define EAT(...)

// Seperate params
#define EXPAND(...) __VA_ARGS__

// Combine params
#define CONCAT_IMP(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMP(a, b)

// Make into string
#define STRINGIFY(x) #x
#define XSTRINGIFY(x) STRINGIFY(x)

// Location as a string
#define CODE_LOCATION "FILE: " __FILE__ " Line: " XSTRINGIFY(__LINE__)

// Get size of array at compile time
template<typename T, size_t N> inline constexpr size_t ARRAY_SIZE(T(&)[N]){return N;}

// String comparison
inline bool strequal(const char* s1, const char* s2)
{
	return strcmp(s1, s2) == 0;
}
