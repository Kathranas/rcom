#pragma once

#include "array_ptr.hpp"
#include "assert.hpp"
#include <cstring>

namespace rcom
{
	template<typename T> T* linear_search(ArrayPtr<T> ptr, const T& value)
	{
		RCOM_ASSERT(ptr, "Null pointer");

		for(size_t i = 0; i < ptr.size(); ++i)
		{
			if(ptr[i] == value)
			{
				return &ptr[i];
			}
		}
		return nullptr;
	}

	inline void zero(BytePtr ptr, int val = 0)
	{
		RCOM_ASSERT(ptr, "Null pointer");

		memset(ptr.data(), val, ptr.byte_size());
	}
	
	inline void copy(BytePtr dst, const BytePtr src)
	{
		RCOM_ASSERT(dst && src, "Null pointer");
		RCOM_ASSERT(dst.byte_size() >= src.byte_size(), "Array too small");

		memcpy(dst.data(), src.data(), src.byte_size());
	}

	inline int compare(const BytePtr dst, const BytePtr src)
	{
		RCOM_ASSERT(dst && src, "Null pointer");
		RCOM_ASSERT(dst.byte_size() >= src.byte_size(), "Array too small");

		return memcmp(dst.data(), src.data(), src.byte_size());
	}

	inline bool equal(const BytePtr dst, const BytePtr src)
	{
		return compare(dst, src) == 0;
	}
}
// namespace::rcom
