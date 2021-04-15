#pragma once

// Basic (but not fundamental) stuff

#include "fundamental.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

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
#define RCOM_CODE_LOCATION "Line: " RCOM_XSTRINGIFY(__LINE__) " File: " __FILE__

// Size of a carray
#define RCOM_CARRAY_SIZE(ARR) (sizeof(ARR) / sizeof(*ARR))

// Asserts
namespace rcom { namespace hidden
{
#if defined(RCOM_OVERRIDE_ASSERTS)
	// Provide your own assert implementation
	extern void assert_imp(const char* fmt, ...);
#else
	// Use default
	inline void assert_imp(const char* fmt, ...)
	{
		va_list argp;
		va_start(argp, fmt);
		vfprintf(stderr, fmt, argp);
		va_end(argp);
		fputc('\n', stderr);
		abort();
	}
#endif
}}
// namespace rcom::hidden

#if defined(RCOM_ASSERTS_ENABLED)
	#define RCOM_ASSERT(x, msg, ...) if(!(x)) rcom::hidden::assert_imp("Failed Assertion: " msg " at: " RCOM_CODE_LOCATION, __VA_ARGS__)
#else
	#define RCOM_ASSERT(x, msg, ...)
#endif

// Defer
namespace rcom { namespace hidden
{
	// Use destructor to Call captured function at end of scope (Scope guard)
	template<typename Func> struct DeferImp
	{
		Func f;
		~DeferImp(){f();}
	};

	// Dummy struct used for the next trick
	struct DeferTemp{};

	// Deduce correct template arguments for DeferImp. No brackets '()' needed
	template<typename Func> DeferImp<Func> operator<<(DeferTemp, Func f)
	{
		return {f};
	};
}}
// namespace rcom::hidden

// We generate a uniquly named DeferImp object, concatinating the line number
// Then deduce the DeferImp template parameters using operator <<
// Finally the exposed lamda captures the outside scope and is used as the block of code to be deferred

// Call block of code at the end of scope
#define RCOM_DEFER_TO_SCOPE auto RCOM_CONCAT(zz_defer_imp, __LINE__) = rcom::hidden::DeferTemp{} << [&]()

// Size of count number of type T in bytes
template<typename T> inline constexpr size_t byte_size(size_t count = 1)
{
	return count * sizeof(T);
}
