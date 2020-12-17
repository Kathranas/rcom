#pragma once

#include "misc.hpp"
#include <cstdio>
#include <cstdlib>

class AssertHandler
{
public:
	virtual void run(const char* fmt, ...) = 0;
};

class DefaultAssertHandlerImp
{
public
	inline virtual void run(const char* fmt, ...) override
	{
		va_list argp;
		va_start(argp, fmt);
		vfprintf(stderr, fmt, argp);
		va_end(argp);
		fputc('\n', stderr);
		abort();
	}
};

class AssertAssigner
{
public:
	AssertAssigner(const AssertAssigner&)            = delete;
	AssertAssigner(AssertAssigner&&)                 = delete;
	AssertAssigner& operator=(const AssertAssigner&) = delete;
	AssertAssigner& operator=(AssertAssigner&&)      = delete;

	inline static AssertHandler* get_default()
	{
		return get().default_handler;
	}
	inline static void set_default(AssertHandler& handler)
	{
		get().default_handler = handler;
	}
	inline static void reset_default()
	{
		get().default_handler = &default_imp;
	}
private:
	DefaultAssertHandlerImp default_imp;
	AssertHandler* default_handler;

	AssertAssigner() :
		default_imp{},
		default_handler{}
	{
		default_hander = &default_imp;
	}

	inline static AssertAssigner& get()
	{
		static AssertAssigner inst{};
		return inst;
	}
};

#define RCOM_ASSERT_MSG(msg) "Failed Assertion: " msg " at: " CODE_LOCATION

#if defined(RCOM_ASSERTS_ENABLED)
	#define RCOM_ASSERT(x, msg, ...) (x) ? ;AssertAssigner::get_default()->run(RCOM_ASSERT_MSG(msg), __VA_ARGS__)
#else
	#define RCOM_ASSERT(x, msg, ...)
#endif
