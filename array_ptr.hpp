#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>

template<typename T> class ArrayPtr;

// Type erased pointer to a constant array of bytes
class ConstBytePtr
{
public:
	ConstBytePtr() = default;
	ConstBytePtr(std::nullptr_t) : data{nullptr}, size{0} {}

	// Size in bytes
	ConstBytePtr(const void* t, size_t n) : data{static_cast<const uint8_t*>(t)}, size{n} {}

	template<typename T> ConstBytePtr(ArrayPtr<T> ptr) : ConstBytePtr(ptr.get(), ptr.size() * sizeof(T)) {}

	// Construct from array. Size is the size of the array
	template<typename T, size_t N> ConstBytePtr(T(&t)[N]) : data{reinterpret_cast<const uint8_t*>(t)}, size{N * sizeof(T)} {}

	// Construct from pointer. Size is size of object pointed to by pointer
	// NOTE: T given instead of T* to not form an ambiguity with array constructor
	template<typename T> ConstBytePtr(T t) : data{reinterpret_cast<const uint8_t*>(t)}, size{sizeof(*t)}{}

	// Const only functions
	inline const uint8_t& operator[](size_t i) const {return data[i];}

	inline const uint8_t* begin() const {return data;}
	inline const uint8_t* end()   const {return data + size;}

	inline const uint8_t* get()   const {return data;}
	inline       size_t   len()   const {return size;}
private:
	const uint8_t* data;
	      size_t   size;
};

// Type erased pointer to an array of bytes
class BytePtr
{
public:
	BytePtr() = default;
	BytePtr(std::nullptr_t) : data{nullptr}, size{0} {}

	// Size in bytes
	BytePtr(void* t, size_t n) : data{static_cast<uint8_t*>(t)}, size{n} {}

	template<typename T> BytePtr(ArrayPtr<T> ptr) : BytePtr(ptr.get(), ptr.len() * sizeof(T)) {}

	// Construct from array. Size is the size of the array
	template<typename T, size_t N> BytePtr(T(&t)[N]) : data{reinterpret_cast<uint8_t*>(t)}, size{N * sizeof(T)} {}

	// Construct from pointer. Size is size of object pointed to by pointer
	// NOTE: T given instead of T* to not form an ambiguity with array constructor
	template<typename T> BytePtr(T t) : data{reinterpret_cast<uint8_t*>(t)}, size{sizeof(*t)}{}

	inline       uint8_t& operator[](size_t i)       {return data[i];};
	inline const uint8_t& operator[](size_t i) const {return data[i];}

	inline       uint8_t* begin()       {return data;}
	inline const uint8_t* begin() const {return data;}
	inline       uint8_t* end()         {return data + size;}
	inline const uint8_t* end()   const {return data + size;}

	inline       uint8_t* get()         {return data;}
	inline const uint8_t* get()   const {return data;}
	inline       size_t   len()   const {return size;}

	// Implicit conversion to const
	operator ConstBytePtr() const {return {data, size};}
private:
	uint8_t* data;
	size_t   size;
};

// Holds a pointer to an array and its size
template<typename T> class ArrayPtr
{
public:
	ArrayPtr() = default;
	ArrayPtr(std::nullptr_t) : data{nullptr}, size{0} {}
	ArrayPtr(T* t, size_t n) : data{t}, size{n} {}

	// Construct from array with correct size
	template<size_t N> ArrayPtr(T(&t)[N]) : data{t}, size{N} {}

	inline       T& operator[](size_t i)       {return data[i];};
	inline const T& operator[](size_t i) const {return data[i];}
 
	inline       T* begin()       {return data;}
	inline const T* begin() const {return data;}
	inline       T* end()         {return data + size;}
	inline const T* end()   const {return data + size;}

	inline       T* get()         {return data;}
	inline const T* get()   const {return data;}
	inline size_t   len()   const {return size;}

	// Implicit conversion to const
	operator ArrayPtr<const T>() const {return {data, size};}
private:
	T*     data;
	size_t size;
};

inline void zero(BytePtr dst)
{
	memset(dst.get(), 0, dst.len());
}

inline void copy(BytePtr dst, ConstBytePtr src)
{
	memcpy(dst.get(), src.get(), src.len());
}
