#pragma once

#include "misc.hpp"
#include "assert.hpp"

namespace rcom
{
	template<typename T> class DynamicArrayPtr
	{
	public:
		inline DynamicArrayPtr();
		inline DynamicArrayPtr(std::nullptr_t);
		inline DynamicArrayPtr(T* ptr, size_t size, size_t count = 0);
		inline operator DynamicArrayPtr<const T>() const;
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
		T*     ptr;
		size_t len;
		size_t num;
	};
	
	template<typename T> DynamicArrayPtr<T>::DynamicArrayPtr()
		: DynamicArrayPtr{nullptr}
	{
	}
	
	template<typename T> DynamicArrayPtr<T>::DynamicArrayPtr(std::nullptr_t)
		: ptr{nullptr}, len{0}, num{0}
	{
	}
	
	template<typename T> DynamicArrayPtr<T>::DynamicArrayPtr(T* init_ptr, size_t init_len, size_t init_count)
		: ptr{init_ptr}, len{init_len}, num{init_count}
	{
	}
	
	template<typename T> DynamicArrayPtr<T>::operator DynamicArrayPtr<const T>() const
	{
		return {ptr, len, num};
	}
	
	template<typename T> DynamicArrayPtr<T>::operator bool() const
	{
		return ptr;
	}

	template<typename T> size_t& DynamicArrayPtr<T>::count()
	{
		return num;
	}
	
	template<typename T> size_t DynamicArrayPtr<T>::count() const
	{
		return num;
	}
	
	template<typename T> T& DynamicArrayPtr<T>::operator[](size_t i)
	{
		RCOM_ASSERT(i < count(), "Index out of range");
		return ptr[i];
	}
	
	template<typename T> const T& DynamicArrayPtr<T>::operator[](size_t i) const
	{
		RCOM_ASSERT(i < count(), "Index out of range");
		return ptr[i];
	}
	 
	template<typename T> T* DynamicArrayPtr<T>::begin()
	{
		return ptr;
	}
	
	template<typename T> const T* DynamicArrayPtr<T>::begin() const
	{
		return ptr;
	}
	
	template<typename T> T* DynamicArrayPtr<T>::end()
	{
		// End of logical array rather than end of capacity
		return &ptr[num];
	}
	
	template<typename T> const T* DynamicArrayPtr<T>::end() const
	{
		return &ptr[num];
	}
	
	template<typename T> T*& DynamicArrayPtr<T>::data()
	{
		return ptr;
	}
	
	template<typename T> const T* DynamicArrayPtr<T>::data() const
	{
		return ptr;
	}
	
	template<typename T> size_t& DynamicArrayPtr<T>::size()
	{
		return len;
	}
	
	template<typename T> size_t  DynamicArrayPtr<T>::size() const
	{
		return len;
	}
}
// namespace rcom
