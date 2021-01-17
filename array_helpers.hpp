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
	
	template<typename T> size_t byte_size(size_t count)
	{
		return count * sizeof(T);
	}

	template<typename T> size_t byte_size(ArrayPtr<T> ptr)
	{
		return byte_size<T>(ptr.size());
	}
	
	template<typename T> rcom::BytePtr to_bytes(rcom::ArrayPtr<T> ptr)
	{
		return {static_cast<uint8_t*>((void*)ptr.data()), byte_size(ptr)};
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
