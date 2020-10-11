#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <type_traits>

template<typename T> class ArrayPtr
{
public:
	inline ArrayPtr();
	inline ArrayPtr(std::nullptr_t);
	inline ArrayPtr(T* t, size_t n);
	template<size_t N>
	inline ArrayPtr(T(&t)[N]);
	inline           operator ArrayPtr<const T>() const;
	inline           operator bool()        const;

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

template<typename T> ArrayPtr<T>::ArrayPtr(std::nullptr_t)
	: data_ptr{nullptr}, data_size{0}
{
}

template<typename T> ArrayPtr<T>::ArrayPtr(T* t, size_t n)
	: data_ptr{t}, data_size{n}
{
}

template<typename T> ArrayPtr<T>::ArrayPtr()
	: ArrayPtr{nullptr}
{
}

template<typename T> template<size_t N> inline ArrayPtr<T>::ArrayPtr(T(&t)[N])
	: ArrayPtr{t, N}
{
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
