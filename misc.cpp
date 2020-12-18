#include "misc.hpp"
#include <cstring>

bool rcom::strequal(const char* s1, const char* s2)
{
	return strlen(s1, s2) == 0;
}

void rcom::die(const char* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	fputc('\n', stderr);
	abort();
}
