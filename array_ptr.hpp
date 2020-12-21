#pragma once

#include "fundamental.hpp"
#include "assert.hpp"

namespace rcom
{
	template<typename T> class ArrayPtr
	{
	public:
		inline ArrayPtr();
		inline ArrayPtr(std::nullptr_t);
		inline ArrayPtr(T* t, size_t n);
		template<size_t N>
		inline ArrayPtr(T(&t)[N]);
	
		inline           operator ArrayPtr<const T>() const;
		inline           operator bool()              const;
	
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
		T*     ptr;
		size_t len;
	};
	
	typedef ArrayPtr<uint8_t> BytePtr;
	
	template<typename T> ArrayPtr<T>::ArrayPtr() :
		ptr{nullptr},
		len{0}
	{
	}
	
	template<typename T> ArrayPtr<T>::ArrayPtr(std::nullptr_t) :
		ArrayPtr{}
	{
	}
	
	template<typename T> ArrayPtr<T>::ArrayPtr(T* t, size_t n) :
		ptr{t},
		len{n}
	{
	}
	
	template<typename T> template<size_t N> inline ArrayPtr<T>::ArrayPtr(T(&t)[N]) :
		ArrayPtr{t, N}
	{
	}
	
	template<typename T> ArrayPtr<T>::operator ArrayPtr<const T>() const
	{
		return {ptr, len};
	}
	
	template<typename T> T& ArrayPtr<T>::operator[](size_t i)
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return ptr[i];
	}
	
	template<typename T> const T& ArrayPtr<T>::operator[](size_t i) const
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return ptr[i];
	}
	
	template<typename T> T* ArrayPtr<T>::begin()
	{
		return ptr;
	}
	
	template<typename T> const T* ArrayPtr<T>::begin() const
	{
		return ptr;
	}
	
	template<typename T> T* ArrayPtr<T>::end()
	{
		return &ptr[len];
	}
	
	template<typename T> const T* ArrayPtr<T>::end() const
	{
		return &ptr[len];
	}
	
	template<typename T> ArrayPtr<T>::operator bool() const
	{
		return ptr;
	}
	
	template<typename T> T*& ArrayPtr<T>::data()
	{
		return ptr;
	}
	
	template<typename T> const T* ArrayPtr<T>::data() const
	{
		return ptr;
	}
	
	template<typename T> size_t& ArrayPtr<T>::size()
	{
		return len;
	}
	
	template<typename T> size_t  ArrayPtr<T>::size() const
	{
		return len;
	}

	// Helper functions

	template<typename T> inline bool operator==(ArrayPtr<T> ptr, std::nullptr_t)
	{
		return !ptr.operator bool();
	}
	
	template<typename T> inline bool operator!=(ArrayPtr<T> ptr, std::nullptr_t)
	{
		return !operator==(ptr, nullptr);
	}

	template<typename T> inline bool operator==(std::nullptr_t, ArrayPtr<T> ptr)
	{
		return operator==(ptr, nullptr);
	}

	template<typename T> inline bool operator!=(std::nullptr_t, ArrayPtr<T> ptr)
	{
		return operator!=(ptr, nullptr);
	}
}
// namespace::rcom
