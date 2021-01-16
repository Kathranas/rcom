#pragma once

#include "fundamental.hpp"
#include "assert.hpp"
#include "array_ptr.hpp"
#include "array_helpers.hpp"

namespace rcom
{
	class Allocator
	{
	public:
		virtual               ~Allocator()            = default;
		virtual rcom::BytePtr alloc(size_t size)      = 0;
		virtual void          free(rcom::BytePtr ptr) = 0;
	
		template<typename T> rcom::ArrayPtr<T> alloc(size_t count);
		template<typename T> void free(rcom::ArrayPtr<T> ptr);
	};

	template<typename T> rcom::ArrayPtr<T> Allocator::alloc(size_t count)
	{
		rcom::BytePtr ptr = alloc(byte_size<T>(count));
		RCOM_ASSERT(ptr, "Failed to allocate");

		return {new(ptr.data())T, count};
	}

	template<typename T> void Allocator::free(rcom::ArrayPtr<T> ptr)
	{
		for(auto& val : ptr)
		{
			~val();
		}
		free(to_bytes(ptr));
	}
}
// namespace rcom
