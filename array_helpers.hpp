#pragma once

#include "array_ptr.hpp"
#include <cstring>

namespace rcom
{
	template<typename T> T* linear_search(ArrayPtr<T> ptr, const T& value)
	{
		for(size_t i = 0; i < ptr.size(); ++i)
		{
			if(ptr[i] == value)
			{
				return &ptr[i];
			}
		}
		return nullptr;
	}
	template<typename T> inline void zero(ArrayPtr<T> ptr, int val = 0)
	{
		memset(ptr.data(), val, byte_size(ptr));
	}
	
	template<typename T, typename U> inline void copy(ArrayPtr<T> dst, const ArrayPtr<U> src)
	{
		memcpy(dst.data(), src.data(), byte_size(src));
	}

	template<typename T, typename U> inline int compare(const ArrayPtr<T> dst, const ArrayPtr<U> src)
	{
		return memcmp(dst.data(), src.data(), src.byte_size());
	}
}
// namespace::rcom
