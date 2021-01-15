#pragma once

#include "array_ptr.hpp"
#include <cstring>

namespace rcom
{
	template<typename T> T& get_first(ArrayPtr<T> ptr)
	{
		return *ptr.begin();
	}
	
	template<typename T> T& get_last(ArrayPtr<T> ptr)
	{
		return *(ptr.end() - 1);
	}
	
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
	
	template<typename T> inline size_t byte_size(ArrayPtr<T> ptr)
	{
		return ptr.size() * sizeof(T);
	}
	
	template<typename T> ArrayPtr<T> to_ptr(T* ptr, size_t n)
	{
		return {ptr, n};
	}
	
	template<typename T, size_t N> ArrayPtr<T> to_ptr(T (&arr)[N])
	{
	    return {arr};
	}
	
	template<typename T> inline void zero(ArrayPtr<T> ptr, int val = 0)
	{
		memset(ptr.data(), val, byte_size(ptr));
	}
	
	template<typename T, typename U> inline void copy(ArrayPtr<T> dst, ArrayPtr<U> src)
	{
		memcpy(dst.data(), src.data(), byte_size(src));
	}

	template<typename T, typename U> inline int compare(ArrayPtr<T> dst, ArrayPtr<U> src)
	{
		return memcmp(dst.data(), src.data(), byte_size(src));
	}
}
// namespace::rcom
