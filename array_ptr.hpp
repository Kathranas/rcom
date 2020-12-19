#pragma once

#include "misc.hpp"

namespace rcom
{
	template<typename T> class ArrayPtr
	{
	public:
		inline ArrayPtr();
		inline ArrayPtr(nullptr_t);
		inline ArrayPtr(T* t, size_t n);
		template<size_t N>
		inline ArrayPtr(T(&t)[N]);
	
		inline           operator ArrayPtr<const T>() const;
		inline           operator bool()              const;
	
		inline       bool operator==(nullptr_t);
		inline       bool operator!=(nullptr_t);
	
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
	private:
		T*     data_ptr;
		size_t data_size;
	};
	
	typedef ArrayPtr<uint8_t> BytePtr;
	
	template<typename T> ArrayPtr<T>::ArrayPtr() :
		data_ptr{nullptr},
		data_size{0}
	{
	}
	
	template<typename T> ArrayPtr<T>::ArrayPtr(nullptr_t) :
		ArrayPtr{}
	{
	}
	
	template<typename T> ArrayPtr<T>::ArrayPtr(T* t, size_t n) :
		data_ptr{t},
		data_size{n}
	{
	}
	
	template<typename T> template<size_t N> inline ArrayPtr<T>::ArrayPtr(T(&t)[N]) :
		ArrayPtr{t, N}
	{
	}
	
	template<typename T> bool ArrayPtr<T>::operator==(nullptr_t)
	{
		return data;
	}
	
	template<typename T> bool ArrayPtr<T>::operator!=(nullptr_t)
	{
		return !operator==(nullptr);
	}
	
	template<typename T> ArrayPtr<T>::operator ArrayPtr<const T>() const
	{
		return {data_ptr, data_size};
	}
	
	template<typename T> T& ArrayPtr<T>::operator[](size_t i)
	{
		return data_ptr[i];
	}
	
	template<typename T> const T& ArrayPtr<T>::operator[](size_t i) const
	{
		return data_ptr[i];
	}
	 
	template<typename T> T* ArrayPtr<T>::begin()
	{
		return data_ptr;
	}
	
	template<typename T> const T* ArrayPtr<T>::begin() const
	{
		return data_ptr;
	}
	
	template<typename T> T* ArrayPtr<T>::end()
	{
		return data_ptr + data_size;
	}
	
	template<typename T> const T* ArrayPtr<T>::end() const
	{
		return data_ptr + data_size;
	}
	
	template<typename T> ArrayPtr<T>::operator bool() const
	{
		return data_ptr;
	}
	
	template<typename T> T*& ArrayPtr<T>::data()
	{
		return data_ptr;
	}
	
	template<typename T> const T* ArrayPtr<T>::data() const
	{
		return data_ptr;
	}
	
	template<typename T> size_t& ArrayPtr<T>::size()
	{
		return data_size;
	}
	
	template<typename T> size_t  ArrayPtr<T>::size() const
	{
		return data_size;
	}
}
// namespace::rcom
