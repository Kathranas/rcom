#pragma once

#include "basic.hpp"
#include <cstring>

namespace rcom
{
	template<typename T> class ArrayPtr;
	typedef ArrayPtr<uint8_t>  BytePtr;

	template<typename T> class ArrayPtr
	{
	public:
		inline ArrayPtr();
		inline ArrayPtr(std::nullptr_t);
		inline ArrayPtr(T* t, size_t n);
		template<size_t N> inline ArrayPtr(T(&t)[N]);
	
		inline operator ArrayPtr<const T>() const;
		inline operator bool()              const;

		inline size_t&   size();
		inline size_t    size()      const;
		inline size_t    byte_size() const;

		inline       BytePtr to_bytes();
		inline const BytePtr to_bytes() const;
	
		inline       T&  operator[](size_t i);
		inline const T&  operator[](size_t i)  const;

		inline       T*  begin();
		inline const T*  begin() const;
		inline       T*  end();
		inline const T*  end()   const;
		inline       T&  first();
		inline const T&  first() const;
		inline       T&  last();
		inline const T&  last()  const;

		inline       T*& data();
		inline const T*  data()  const;
	private:
		T*     ptr;
		size_t len;
	};
	
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

	template<typename T> T& ArrayPtr<T>::first()
	{
		RCOM_ASSERT(size() > 0, "Index out of range");
		return ptr[0];
	}

	template<typename T> const T& ArrayPtr<T>::first() const
	{
		RCOM_ASSERT(size() > 0, "Index out of range");
		return ptr[0];
	}

	template<typename T> T& ArrayPtr<T>::last()
	{
		RCOM_ASSERT(size() > 0, "Index out of range");
		return ptr[size() - 1];
	}

	template<typename T> const T& ArrayPtr<T>::last() const
	{
		RCOM_ASSERT(size() > 0, "Index out of range");
		return ptr[size() - 1];
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

	template<typename T> size_t ArrayPtr<T>::byte_size() const
	{
		return size() * sizeof(T);
	}

	template<typename T> rcom::BytePtr ArrayPtr<T>::to_bytes()
	{
		return {static_cast<uint8_t*>((void*)data()), byte_size()};
	}

	template<typename T> const rcom::BytePtr ArrayPtr<T>::to_bytes() const
	{
		return {static_cast<uint8_t*>((void*)data()), byte_size()};
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

	template<typename T> inline ArrayPtr<T> to_ptr(T* ptr, size_t n)
	{
		return {ptr, n};
	}
	
	template<typename T, size_t N> inline ArrayPtr<T> to_ptr(T (&arr)[N])
	{
	    return {arr};
	}

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

	inline void zero_mem(BytePtr ptr, int val = 0)
	{
		RCOM_ASSERT(ptr, "Null pointer");

		memset(ptr.data(), val, ptr.byte_size());
	}
	
	inline void copy_mem(BytePtr dst, const BytePtr src)
	{
		RCOM_ASSERT(dst && src, "Null pointer");
		RCOM_ASSERT(dst.byte_size() >= src.byte_size(), "Array too small");

		memcpy(dst.data(), src.data(), src.byte_size());
	}

	inline int compare_mem(const BytePtr dst, const BytePtr src)
	{
		RCOM_ASSERT(dst && src, "Null pointer");
		RCOM_ASSERT(dst.byte_size() >= src.byte_size(), "Array too small");

		return memcmp(dst.data(), src.data(), src.byte_size());
	}

	inline bool equal_mem(const BytePtr dst, const BytePtr src)
	{
		return compare_mem(dst, src) == 0;
	}
}
// namespace::rcom
