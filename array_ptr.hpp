#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>

// Forward declaration
template<typename T> struct ArrayPtr;

// Const type erased array pointer
template<> struct ArrayPtr<const void>
{
	const uint8_t* data;
	size_t         size;

	// Compiler generated default constructor
	ArrayPtr() = default;

	// Construct from nullptr
	ArrayPtr(std::nullptr_t) : data{nullptr}, size{0} {}

	// Construct from const pointer and size in bytes
	ArrayPtr(const void* t, size_t n) : data{static_cast<const uint8_t*>(t)}, size{n} {}

	// Construct from const ArrayPtr
	template<typename T> ArrayPtr(ArrayPtr<const T> ptr) : ArrayPtr(ptr.data, ptr.size) {}

	// Construct from const array. Size is the size of the array
	template<typename T, size_t N> ArrayPtr(const T(&t)[N]) : data{reinterpret_cast<const byte*>(t)}, size{N * sizeof(T)} {}

	// Construct from pointer. Size is size of object pointed to by pointer
	// NOTE: T given instead of T* to not form an ambiguity with array constructor
	template<typename T> ArrayPtr(const T t) : data{reinterpret_cast<const byte*>(t)}, size{sizeof(*t)}{}

	// Array access
	const uint8_t& operator[](size_t i) const {return data[i];}

	// Used by range for loop
	const uint8_t* begin() const {return data;}
	const uint8_t* end()   const {return data + size;}
};

// Non const type erase array pointer
template<> struct ArrayPtr<void>
{
	uint8_t* data;
	size_t   size;

	// Compiler generated default constructor
	ArrayPtr() = default;

	// Construct from nullptr
	ArrayPtr(std::nullptr_t) : data{nullptr}, size{0} {}

	// Construct from non const pointer and size in bytes
	ArrayPtr(void* t, size_t n) : data{static_cast<uint8_t*>(t)}, size{n} {}

	// Construct from non const array. Size is the size of the array
	template<typename T, size_t N> ArrayPtr(T(&t)[N]) : data{reinterpret_cast<byte*>(t)}, size{N * sizeof(T)} {}

	// Construct from pointer. Size is size of object pointed to by pointer
	// NOTE: T given instead of T* to not form an ambiguity with array constructor
	template<typename T> ArrayPtr(T t) : data{reinterpret_cast<byte*>(t)}, size{sizeof(*t)}{}

	// Construct from non const ArrayPtr
	template<typename T> ArrayPtr(ArrayPtr<T> ptr) : ArrayPtr(ptr.data, ptr.size) {}

	// Array access
	      uint8_t& operator[](size_t i)       {return data[i];};
	const uint8_t& operator[](size_t i) const {return data[i];}

	// Used by range for loop
	      uint8_t* begin()       {return data;}
	const uint8_t* begin() const {return data;}
	      uint8_t* end()         {return data + size;}
	const uint8_t* end()   const {return data + size;}

	// Implicit conversion to const
	operator ArrayPtr<const void>() const {return {data, size};}
};

// Holds a pointer to an array and its size
template<typename T> struct ArrayPtr
{
	T*     data;
	size_t size;

	// Compiler generated default constructor
	ArrayPtr() = default;

	// Construct from nullptr
	ArrayPtr(std::nullptr_t) : data{nullptr}, size{0} {}

	// Construct from pointer and size
	ArrayPtr(T* t, size_t n) : data{t}, size{n} {}

	// Construct from array with correct size
	template<size_t N> ArrayPtr(T(&t)[N]) : data{t}, size{N} {}

	// Array access
	      T& operator[](size_t i)       {return data[i];};
	const T& operator[](size_t i) const {return data[i];}

	// Used by range for loop
	      T* begin()       {return data;}
	const T* begin() const {return data;}
	      T* end()         {return data + size;}
	const T* end()   const {return data + size;}

	// Implicit conversion to const
	operator ArrayPtr<const T>() const {return {data, size};}
};

inline void zero(ArrayPtr<void> dst)
{
	memset(dst.data, 0, dst.size);
}

inline void copy(ArrayPtr<void> dst, ArrayPtr<const void> src)
{
	memcpy(dst.data, src.data, src.size);
}
