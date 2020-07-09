#pragma once

#include <cstdlib>
#include <cstdio>

inline void assert_imp(bool x, const char* msg, const char* file, int line)
{
	if(!x)
	{
		// Log the failed assertion
		fprintf(stderr, "Assert failed: %s\n file: %s\n line: %i\n", msg, file, line);

		// Crash
		abort();
	}
}

#if defined(RCOM_ASSERTS_ENABLED)
	// Make sure this condition is true
	#define ASSERT_TRUE(x, msg) assert_imp((x), (msg), __FILE__, __LINE__)

	// Make sure this condition is false
	#define ASSERT_FALSE(x, msg) assert_imp(!(x), (msg), __FILE__, __LINE__)
#else
	#define ASSERT_TRUE(x, msg)
	#define ASSERT_FALSE(x, msg)
#endif
