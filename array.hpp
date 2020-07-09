#pragma once

#include <cstddef>
#include <cstring>

// Holds a ponter to a array and its size
template<typename T> struct ArrayPtr
{
	T*     data;
	size_t size;

	// Array access
	      T& operator[](size_t i)       {return data[i];};
	const T& operator[](size_t i) const {return data[i];}

	// Implicit conversion to const
	operator ArrayPtr<const T>() const {return {data, size};}
};

// Wrapper around an array that knows its own size
template<typename T, size_t N> struct Array
{
	static const size_t size = N;
	T data[size];

	// Use default constructor + destructor
	Array()                        = default;
	~Array()                       = default;

	// Disable copy / move construction
	Array(const Array&)            = delete;
	Array(Array&&)                 = delete;
	Array& operator=(const Array&) = delete;
	Array& operator=(Array&&)      = delete;

	// Array access
	      T& operator[](size_t i)       {return data[i];}
	const T& operator[](size_t i) const {return data[i];}

	// Used by range for loop
	T* begin(){return data;};
	T* end(){return data + size;};

	// Get an array pointer
	inline ArrayPtr<T>       ptr()      {return {data, size};}
	inline ArrayPtr<const T> ptr() const{return {data, size};}
};

