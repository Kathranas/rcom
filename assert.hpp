#pragma once

#include "misc.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

namespace rcom
{
	class AssertHandler
	{
	public:
		virtual void run(const char* fmt, ...) = 0;
	};
	
	class DefaultAssertHandlerImp : public AssertHandler
	{
	public:
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
	
	// Singleton for getting / setting assert handlers
	class AssertTable
	{
	public:
		AssertTable(const AssertTable&)            = delete;
		AssertTable(AssertTable&&)                 = delete;
		AssertTable& operator=(const AssertTable&) = delete;
		AssertTable& operator=(AssertTable&&)      = delete;
	
		inline static AssertHandler* get_default()
		{
			return get().default_handler;
		}
		inline static void set_default(AssertHandler& handler)
		{
			get().default_handler = &handler;
		}
		inline static void reset_default()
		{
			auto& self = get();
			self.default_handler = &self.default_imp;
		}
	private:
		DefaultAssertHandlerImp default_imp;
		AssertHandler* default_handler;
	
		AssertTable() :
			default_imp{},
			default_handler{}
		{
			default_handler = &default_imp;
		}
	
		inline static AssertTable& get()
		{
			static AssertTable inst{};
			return inst;
		}
	};

}
// namespace::rcom

#define RCOM_ASSERT_MSG(msg) "Failed Assertion: " msg " at: " RCOM_CODE_LOCATION

#if defined(RCOM_ASSERTS_ENABLED)
	#define RCOM_ASSERT(x, msg, ...) (x) ? ;rcom::AssertAssigner::get_default()->run(RCOM_ASSERT_MSG(msg), __VA_ARGS__)
#else
	#define RCOM_ASSERT(x, msg, ...)
#endif
