#pragma once

#include "array_ptr.hpp"
#include "array.hpp"
#include "dynamic_array.hpp"
#include <type_traits>
#include <cstring>
#include <type_traits>

namespace rcom
{
	template<typename T, typename... Ts> constexpr Array<std::decay_t<T>, 1 + sizeof... (Ts)> make_array(T&& t, Ts&&... ts) noexcept(noexcept(std::is_nothrow_constructible<Array<std::decay_t<T>, 1 + sizeof... (Ts)>, T&&, Ts&&...>::value))
	{
	    return {{std::forward<T>(t), std::forward<Ts>(ts)...}};
	}
	
	template<typename T> constexpr Array<std::decay<T>, 0> make_array() noexcept
	{
	    return {};
	}

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
	
	template<typename T> ArrayPtr<T> to_ptr(ArrayPtr<T> ptr)
	{
	    return ptr;
	}
	
	template<typename T> ArrayPtr<T> to_ptr(T* ptr, size_t n)
	{
		return {ptr, n};
	}
	
	template<typename T, size_t N> ArrayPtr<T> to_ptr(T (&arr)[N])
	{
	    return {arr};
	}
	
	template<typename T> ArrayPtr<typename T::value_type> to_ptr(T& t)
	{
	    return {t};
	}
	
	template<typename T> ArrayPtr<const typename T::value_type> to_ptr(const T& t)
	{
	    return {t};
	}
	
	template<typename T, size_t N> ArrayPtr<T> to_ptr(Array<T, N>& arr)
	{
		return {arr.data(), arr.size()};
	}
	
	template<typename T, size_t N> ArrayPtr<const T> to_ptr(const Array<T, N>& arr)
	{
		return {arr.data(), arr.size()};
	}
	
//	template<typename T> inline ArrayPtr<T> to_ptr(DynamicArray<T> arr)
//	{
//		return {arr.data(), arr.count()};
//	}
	
	template<typename T> inline void zero(ArrayPtr<T> ptr, int val = 0)
	{
		static_assert(!std::is_const<T>(), "Cannot zero const array");
		memset(ptr.data(), val, byte_size(ptr));
	}
	
	template<typename T, typename U> inline void copy(ArrayPtr<T> dst, ArrayPtr<U> src)
	{
		static_assert(!std::is_const<T>(),  "Cannot copy to const array");
		memcpy(dst.data(), src.data(), byte_size(src));
	}

	template<typename T, typename U> inline int compare(ArrayPtr<T> dst, ArrayPtr<U> src)
	{
		return memcmp(dst.data(), src.data(), byte_size(src));
	}
}
// namespace::rcom
