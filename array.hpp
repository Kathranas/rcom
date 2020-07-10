#pragma once

#include "macros.hpp"

// size_t
#include <cstddef>

// Holds a ponter to a array and its size
template<typename T> struct ArrayPtr
{
	T*     data;
	size_t size;

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

// Creates an ArrayPtr from a c array
#define ARRAY_PTR(x) ArrayPtr<std::remove_all_extents<decltype(x)>::type>{x, ARRAY_SIZE(x)}

// Wrapper around an array that knows its own size
template<typename T, size_t N> struct Array
{
	static const size_t size = N;
	T data[size];

	// Use default constructor + destructor
	Array()                        = default;
	~Array()                       = default;

	// Allow move construction
	Array(Array&&)                 = default;
	Array& operator=(Array&&)      = default;

	// Disable copy construction
	Array(const Array&)            = delete;
	Array& operator=(const Array&) = delete;

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

// Deduce the size of the array from input params
template<typename T, typename... TS> Array<T, sizeof...(TS)> make_array(TS&&... t)
{
	return {t...};
}
