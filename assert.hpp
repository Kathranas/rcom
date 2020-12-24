#pragma once

#include "misc.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

namespace rcom
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
}
// namespace RCOM

#define RCOM_ASSERT_MSG(msg) "Failed Assertion: " msg " at: " RCOM_CODE_LOCATION

#if defined(RCOM_ASSERTS_ENABLED)
	#define RCOM_ASSERT(x, msg, ...) if(x) rcom::assert_imp(RCOM_ASSERT_MSG(msg), __VA_ARGS__)
#else
	#define RCOM_ASSERT(x, msg, ...)
#endif
