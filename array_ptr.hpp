#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>

template<typename T> class ArrayPtr;

// Type erased pointer to a constant array of bytes
class ByteView
{
public:
	const uint8_t* data;
	const size_t   size;

	inline ByteView();
	inline ByteView(std::nullptr_t);

	// Size in bytes
	inline ByteView(const void* t, size_t n);

	template<typename T> inline ByteView(ArrayPtr<T> ptr);

	// Construct from array. Size is the size of the array
	template<typename T, size_t N> inline ByteView(T(&t)[N]);

	// Construct from pointer. Size is size of object pointed to by pointer
	// NOTE: T given instead of T* to not form an ambiguity with array constructor
	template<typename T> inline ByteView(T t);

	inline                operator bool()      const;
	inline const uint8_t& operator[](size_t i) const;
	inline const uint8_t* begin()              const;
	inline const uint8_t* end()                const;
};

ByteView::ByteView(std::nullptr_t)
	: data{nullptr}, size{0}
{
}

ByteView::ByteView()
	: ByteView(nullptr)
{
}

ByteView::ByteView(const void* t, size_t n)
	: data{static_cast<const uint8_t*>(t)}, size{n}
{
}

template<typename T> ByteView::ByteView(ArrayPtr<T> ptr)
	: ByteView(ptr.data, ptr.size * sizeof(T))
{
}

template<typename T, size_t N> ByteView::ByteView(T(&t)[N])
	: data{reinterpret_cast<const uint8_t*>(t)}, size{N * sizeof(T)}
{
}

template<typename T> ByteView::ByteView(T t)
	: data{reinterpret_cast<const uint8_t*>(t)}, size{sizeof(T)}
{
}

inline const uint8_t& ByteView::operator[](size_t i) const
{
	return data[i];
}

const uint8_t* ByteView::end() const
{
	return data + size;
}

const uint8_t* ByteView::begin() const
{
	return data;
}

ByteView::operator bool() const
{
	return data;
}

// Type erased pointer to an array of bytes
class BytePtr
{
public:
	uint8_t* data;
	size_t   size;

	inline BytePtr();
	inline BytePtr(std::nullptr_t);

	// Size in bytes
	inline BytePtr(void* t, size_t n);

	template<typename T> inline BytePtr(ArrayPtr<T> ptr);

	// Construct from array. Size is the size of the array
	template<typename T, size_t N> inline BytePtr(T(&t)[N]);

	// Construct from pointer. Size is size of object pointed to by pointer
	// NOTE: T given instead of T* to not form an ambiguity with array constructor
	template<typename T> inline BytePtr(T t);

	inline operator bool()                     const;
	inline operator ByteView()                 const;

	inline       uint8_t& operator[](size_t i);
	inline const uint8_t& operator[](size_t i) const;

	inline       uint8_t* begin();
	inline const uint8_t* begin()              const;
	inline       uint8_t* end();
	inline const uint8_t* end()                const;

};

BytePtr::BytePtr()
	: BytePtr(nullptr)
{
}

BytePtr::BytePtr(std::nullptr_t)
	: data{nullptr}, size{0}
{
}

	// Size in bytes
BytePtr::BytePtr(void* t, size_t n)
	: data{static_cast<uint8_t*>(t)}, size{n}
{
}

template<typename T> BytePtr::BytePtr(ArrayPtr<T> ptr)
	: BytePtr(ptr.data, ptr.size * sizeof(T))
{
}

template<typename T, size_t N> BytePtr::BytePtr(T(&t)[N])
	: data{reinterpret_cast<uint8_t*>(t)}, size{N * sizeof(T)}
{
}

template<typename T> BytePtr::BytePtr(T t)
	: data{reinterpret_cast<uint8_t*>(t)}, size{sizeof(*t)}
{
}

      uint8_t& BytePtr::operator[](size_t i)
{
	return data[i];
}

const uint8_t& BytePtr::operator[](size_t i) const
{
	return data[i];
}

uint8_t* BytePtr::begin()
{
	return data;
}

const uint8_t* BytePtr::begin() const
{
	return data;
}

uint8_t* BytePtr::end()
{
	return data + size;
}

const uint8_t* BytePtr::end() const
{
	return data + size;
}

BytePtr::operator bool() const
{
	return data;
}

BytePtr::operator ByteView() const
{
	return {data, size};
}

// Holds a pointer to an array and its size
template<typename T> class ArrayPtr
{
public:
	T*     data;
	size_t size;

	inline ArrayPtr();
	inline ArrayPtr(std::nullptr_t);
	inline ArrayPtr(T* t, size_t n);

	// Construct from array with correct size
	template<size_t N> inline ArrayPtr(T(&t)[N]);

	inline operator bool()                const;
	inline operator ArrayPtr<const T>()   const;

	inline       T& operator[](size_t i);
	inline const T& operator[](size_t i)  const;
 
	inline       T* begin();
	inline const T* begin()               const;
	inline       T* end();
	inline const T* end()                 const;

};

template<typename T> ArrayPtr<T>::ArrayPtr()
	: ArrayPtr(nullptr)
{
}

template<typename T> ArrayPtr<T>::ArrayPtr(std::nullptr_t) 
	: data{nullptr}, size{0}
{
}

template<typename T> ArrayPtr<T>::ArrayPtr(T* t, size_t n) 
	: data{t}, size{n}
{
}

// Construct from array with correct size
template<typename T> template<size_t N> ArrayPtr<T>::ArrayPtr(T(&t)[N]) 
	: data{t}, size{N}
{
}

template<typename T> T& ArrayPtr<T>::operator[](size_t i)
{
	return data[i];
}

template<typename T> const T& ArrayPtr<T>::operator[](size_t i) const
{
	return data[i];
}
 
template<typename T> T* ArrayPtr<T>::begin()
{
	return data;
}

template<typename T> const T* ArrayPtr<T>::begin() const 
{
	return data;
}

template<typename T> T* ArrayPtr<T>::end()
{
	return data + size;
}

template<typename T> const T* ArrayPtr<T>::end() const
{
	return data + size;
}

template<typename T> ArrayPtr<T>::operator bool() const
{
	return data;
}

template<typename T> ArrayPtr<T>::operator ArrayPtr<const T>() const
{
	return {data, size};
}

inline void zero(BytePtr dst, int val = 0)
{
	memset(dst.data, val, dst.size);
}

inline void copy(BytePtr dst, ByteView src)
{
	memcpy(dst.data, src.data, src.size);
}
