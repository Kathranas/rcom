#pragma once

#include "fundamental.hpp"
#include "assert.hpp"
#include "array_ptr.hpp"
#include "array_helpers.hpp"

namespace rcom
{
	template<typename T> constexpr size_t byte_size(size_t count)
	{
		return count * sizeof(T);
	}

	class Allocator
	{
	public:
		virtual         ~Allocator()       = default;
		virtual BytePtr alloc(size_t size) = 0;
		virtual void    free(BytePtr ptr)  = 0;
	
		template<typename T> ArrayPtr<T> alloc(size_t count);
		template<typename T> void        free(ArrayPtr<T> ptr);
	};

	template<typename T> ArrayPtr<T> Allocator::alloc(size_t count)
	{
		BytePtr ptr = alloc(byte_size<T>(count));
		RCOM_ASSERT(ptr, "Failed to allocate");

		return {new(ptr.data())T, count};
	}

	template<typename T> void Allocator::free(ArrayPtr<T> ptr)
	{
		for(auto& val : ptr)
		{
			~val();
		}
		free(to_bytes(ptr));
	}
}
// namespace rcom
