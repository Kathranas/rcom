#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstring>

// Common typedefs
typedef uint8_t byte;

// Remove params
#define EAT(...)

// Seperate params
#define EXPAND(...) __VA_ARGS__

// Combine params
#define CONCAT_IMP(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMP(a, b)

// Make into string
#define STRINGIFY(x) #x
#define XSTRINGIFY(x) STRINGIFY(x)

// Get size of array at compile time
template<typename T, size_t N> inline constexpr size_t ARRAY_SIZE(T(&)[N]){return N;}

// Assert implementation
namespace
{
	inline void assert_imp(bool x, const char* msg, const char* file, int line)
	{
		if(!x)
		{
			// Log the failed assertion
			fprintf(stderr, "Assert failed: %s\n file: %s\n line: %i\n", msg, file, line);
	
			// Crash
			abort();
		}
	}
}

#if defined(RCOM_ASSERTS_ENABLED)
	// Make sure this condition is true
	#define ASSERT_TRUE(x, msg) assert_imp((x), (msg), __FILE__, __LINE__)

	// Make sure this condition is false
	#define ASSERT_FALSE(x, msg) assert_imp(!(x), (msg), __FILE__, __LINE__)
#else
	#define ASSERT_TRUE(x, msg)
	#define ASSERT_FALSE(x, msg)
#endif

// Forward declaration
template<typename T> struct ArrayPtr;

// Const type erased array pointer
template<> struct ArrayPtr<const void>
{
	const byte* data;
	size_t      size;

	// Compiler generated default constructor
	ArrayPtr() = default;

	// Construct from nullptr
	ArrayPtr(std::nullptr_t) : data{nullptr}, size{0} {}

	// Construct from const pointer and size in bytes
	ArrayPtr(const void* t, size_t n) : data{static_cast<const byte*>(t)}, size{n} {}

	// Construct from const ArrayPtr
	template<typename T> ArrayPtr(ArrayPtr<const T> ptr) : ArrayPtr(ptr.data, ptr.size) {}

	// Construct from const array. Size is the size of the array
	template<typename T, size_t N> ArrayPtr(const T(&t)[N]) : data{reinterpret_cast<const byte*>(t)}, size{N * sizeof(T)} {}

	// Construct from pointer. Size is size of object pointed to by pointer
	// NOTE: T given instead of T* to not form an ambiguity with array constructor
	template<typename T> ArrayPtr(const T t) : data{reinterpret_cast<const byte*>(t)}, size{sizeof(*t)}{}

	// Array access
	const byte& operator[](size_t i) const {return data[i];}

	// Used by range for loop
	const byte* begin() const {return data;}
	const byte* end()   const {return data + size;}
};

// Non const type erase array pointer
template<> struct ArrayPtr<void>
{
	byte*  data;
	size_t size;

	// Compiler generated default constructor
	ArrayPtr() = default;

	// Construct from nullptr
	ArrayPtr(std::nullptr_t) : data{nullptr}, size{0} {}

	// Construct from non const pointer and size in bytes
	ArrayPtr(void* t, size_t n) : data{static_cast<byte*>(t)}, size{n} {}

	// Construct from non const array. Size is the size of the array
	template<typename T, size_t N> ArrayPtr(T(&t)[N]) : data{reinterpret_cast<byte*>(t)}, size{N * sizeof(T)} {}

	// Construct from pointer. Size is size of object pointed to by pointer
	// NOTE: T given instead of T* to not form an ambiguity with array constructor
	template<typename T> ArrayPtr(T t) : data{reinterpret_cast<byte*>(t)}, size{sizeof(*t)}{}

	// Construct from non const ArrayPtr
	template<typename T> ArrayPtr(ArrayPtr<T> ptr) : ArrayPtr(ptr.data, ptr.size) {}

	// Array access
	      byte& operator[](size_t i)       {return data[i];};
	const byte& operator[](size_t i) const {return data[i];}

	// Used by range for loop
	      byte* begin()       {return data;}
	const byte* begin() const {return data;}
	      byte* end()         {return data + size;}
	const byte* end()   const {return data + size;}

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
	ASSERT_TRUE(dst.data, "Destination array is null");
	ASSERT_TRUE(dst.size > 0, "Destination array has zero size");
	memset(dst.data, 0, dst.size);
}

inline void copy(ArrayPtr<void> dst, ArrayPtr<const void> src)
{
	ASSERT_TRUE(dst.data, "Destination array is null");
	ASSERT_TRUE(src.data, "Source array is null");
	ASSERT_TRUE(dst.size >= src.size, "Destination array is too small");
	memcpy(dst.data, src.data, src.size);
}

// String comparison
inline bool strequal(const char* s1, const char* s2)
{
	return strcmp(s1, s2) == 0;
}

// Implementation of the defer macro
namespace
{
	// Use destructor to Call captured function at end of scope (Scope guard)
	template<typename Func> struct DeferImp
	{
		Func f;
		~DeferImp(){f();}
	};

	// Dummy struct used for the next trick
	struct DeferTemp{};

	// Deduce correct template arguments for DeferImp. No brackets '()' needed
	template<typename Func> DeferImp<Func> operator<<(DeferTemp, Func f)
	{
		return {f};
	};
}
// We generate a uniquly named DeferImp object, concatinating the line number
// Then deduce the DeferImp template parameters using operator <<
// Finally the exposed lamda captures the outside scope and is used as the block of code to be deferred

// Call block of code at the end of scope
#define DEFER_TO_SCOPE auto CONCAT(zz_defer_imp, __LINE__) = DeferTemp{} << [&]()


