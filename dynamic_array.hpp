#pragma once

#include "misc.hpp"
#include "assert.hpp"

namespace rcom
{
	template<typename T> class DynamicArray
	{
	public:
		inline DynamicArray();
		inline DynamicArray(std::nullptr_t);
		inline DynamicArray(T* ptr, size_t size, size_t count = 0);
		template<size_t N>
		inline DynamicArray(T(&arr)[N], size_t count = 0);
		inline operator DynamicArray<const T>() const;
		inline operator bool()                  const;
	
		inline       T&  operator[](size_t i);
		inline const T&  operator[](size_t i)   const;
		inline       T*  begin();
		inline const T*  begin()                const;
		inline       T*  end();
		inline const T*  end()                  const;
		inline       T*& data();
		inline const T*  data()                 const;
		inline size_t&   size();
		inline size_t    size()                 const;
		inline size_t&   count();
		inline size_t    count()                const;
	private:
		// Pointer to array
		T*     ptr;

		// Physical Size / Capacity
		size_t len;

		// Logical size / Number of elements
		size_t num;
	};
	
	template<typename T> DynamicArray<T>::DynamicArray()
		: DynamicArray{nullptr}
	{
	}
	
	template<typename T> DynamicArray<T>::DynamicArray(std::nullptr_t)
		: ptr{nullptr}, len{0}, num{0}
	{
	}
	
	template<typename T> DynamicArray<T>::DynamicArray(T* p, size_t size, size_t count)
		: ptr{p}, len{size}, num{count}
	{
	}
	
	template<typename T> template<size_t N> DynamicArray<T>::DynamicArray(T(&arr)[N], size_t count)
		: DynamicArray{arr, N, count}
	{
	}
	
	template<typename T> DynamicArray<T>::operator DynamicArray<const T>() const
	{
		return {ptr, len, count};
	}
	
	template<typename T> DynamicArray<T>::operator bool() const
	{
		return ptr;
	}

	template<typename T> size_t& DynamicArray<T>::count()
	{
		return num;
	}
	
	template<typename T> size_t DynamicArray<T>::count() const
	{
		return num;
	}
	
	template<typename T> T& DynamicArray<T>::operator[](size_t i)
	{
		RCOM_ASSERT(i < count(), "Index out of range");
		return ptr[i];
	}
	
	template<typename T> const T& DynamicArray<T>::operator[](size_t i) const
	{
		RCOM_ASSERT(i < count(), "Index out of range");
		return ptr[i];
	}
	 
	template<typename T> T* DynamicArray<T>::begin()
	{
		return ptr;
	}
	
	template<typename T> const T* DynamicArray<T>::begin() const
	{
		return ptr;
	}
	
	template<typename T> T* DynamicArray<T>::end()
	{
		// End of logical array rather than end of capacity
		return &ptr[num];
	}
	
	template<typename T> const T* DynamicArray<T>::end() const
	{
		return &ptr[num];
	}
	
	template<typename T> T*& DynamicArray<T>::data()
	{
		return ptr;
	}
	
	template<typename T> const T* DynamicArray<T>::data() const
	{
		return ptr;
	}
	
	template<typename T> size_t& DynamicArray<T>::size()
	{
		return len;
	}
	
	template<typename T> size_t  DynamicArray<T>::size() const
	{
		return len;
	}
}
// namespace rcom
