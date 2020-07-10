#pragma once

#include <cstddef>
#include <type_traits>

// Remove params
#define EAT(...)

// Seperate params
#define EXPAND(...) __VA_ARGS__

// Combine params
#define CONCAT_1(a, b) a ## b
#define CONCAT(a, b) CONCAT_1(a, b)

// Make into string
#define STRINGIFY(x) #x

// Implementation of array size macro
namespace
{
	template<typename T> inline constexpr size_t array_size_imp()
	{
		static_assert(std::is_array<T>(), "SIZE type is not an array");
		return std::extent<T>::value;
	}
}

// Gets the size of the array. Static assert for array types
#define ARRAY_SIZE(x) array_size_imp<decltype(x)>()

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
