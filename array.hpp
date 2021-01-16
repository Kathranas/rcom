#pragma once

#include "fundamental.hpp"
#include "assert.hpp"
#include "array_ptr.hpp"
#include <initializer_list>

namespace rcom
{
	// Multidimensional array
	template<typename T, size_t N, size_t... NS> class Array;

	template<typename T, size_t N> class Array<T, N>
	{
	public:
		// Required to be an aggrigate
		T _arr[N]; // Do not access this directly. Use data() instead
		Array(const Array&)            = default;
		Array(Array&&)                 = default;

		Array& operator=(const Array&) = default;
		Array& operator=(Array&&)      = default;
		~Array()                       = default;

		// ArrayPtr Conversion
		inline operator ArrayPtr<T>();
		inline operator ArrayPtr<const T>() const;
		inline ArrayPtr<T>       to_ptr();
		inline ArrayPtr<const T> to_ptr() const;
	
		inline       T&  operator[](size_t i);
		inline const T&  operator[](size_t i)   const;
		inline       T*  begin();
		inline const T*  begin()                const;
		inline       T*  end();
		inline const T*  end()                  const;
		inline       T*  data();
		inline const T*  data()                 const;
		inline static constexpr size_t size();

		// Multidimensional
		inline static constexpr size_t flat_size();
		inline static constexpr size_t sub_array_count();
	};

#define RCOM_MAKE_ARRAY(NAME, TYPE, ...)  rcom::Array<TYPE, std::initializer_list<TYPE>__VA_ARGS__.size()> NAME{__VA_ARGS__}
#define RCOM_FROM_STRING(NAME, TYPE, ARR) rcom::Array<TYPE, (sizeof(ARR) / sizeof(*ARR))> NAME{ARR}

	template<typename T, size_t N> ArrayPtr<T> Array<T, N>::to_ptr()
	{
		return {data(), N};
	}

	template<typename T, size_t N> ArrayPtr<const T> Array<T, N>::to_ptr() const
	{
		return {data(), N};
	}

	template<typename T, size_t N> Array<T, N>::operator ArrayPtr<T>()
	{
		return to_ptr();
	}

	template<typename T, size_t N> Array<T, N>::operator ArrayPtr<const T>() const
	{
		return to_ptr();
	}
	
	template<typename T, size_t N> T& Array<T, N>::operator[](size_t i)
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return _arr[i];
	}
	
	template<typename T, size_t N> const T& Array<T, N>::operator[](size_t i) const
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return _arr[i];
	}
	
	template<typename T, size_t N> T* Array<T, N>::begin()
	{
		return &_arr[0];
	}
	
	template<typename T, size_t N> const T* Array<T, N>::begin() const
	{
		return &_arr[0];
	}
	
	template<typename T, size_t N> T* Array<T, N>::end()
	{
		return &_arr[N];
	}
	
	template<typename T, size_t N> const T* Array<T, N>::end() const
	{
		return &_arr[N];
	}
	
	template<typename T, size_t N> const T* Array<T, N>::data() const
	{
		return &_arr[0];
	}
	
	template<typename T, size_t N> T* Array<T, N>::data()
	{
		return &_arr[0];
	}
	
	template<typename T, size_t N> constexpr size_t Array<T, N>::size()
	{
		return N;
	}

	template<typename T, size_t N> constexpr size_t Array<T, N>::flat_size()
	{
		return size();
	}

	// Multidimensional array
	template<typename T, size_t N, size_t... NS> class Array
	{
	public:
		typedef Array<T, NS...> ArrayType;

		// Required to be an aggrigate
		Array<ArrayType, N> _arr;
		Array(const Array&)            = default;
		Array(Array&&)                 = default;

		Array& operator=(const Array&) = default;
		Array& operator=(Array&&)      = default;
		~Array()                       = default;

		// ArrayPtr conversion
		inline operator ArrayPtr<ArrayType>();
		inline operator ArrayPtr<const ArrayType>() const;
		inline ArrayPtr<ArrayType>       to_ptr();
		inline ArrayPtr<const ArrayType> to_ptr() const;

		inline       ArrayType& operator[](size_t i);
		inline const ArrayType& operator[](size_t i)  const;
		inline       ArrayType* begin();
		inline const ArrayType* begin()               const;
		inline       ArrayType* end();
		inline const ArrayType* end()                 const;
		inline       ArrayType* data();
		inline const ArrayType* data()                const;
		inline static constexpr size_t size();

		// Multidimensional
		inline static constexpr size_t flat_size();
		inline static constexpr size_t sub_array_count();
	};

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::to_ptr()       -> ArrayPtr<ArrayType>
	{
		return {data(), N};
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::to_ptr() const -> ArrayPtr<const ArrayType>
	{
		return {data(), N};
	}

	template<typename T, size_t N, size_t... NS> Array<T, N, NS...>::operator ArrayPtr<Array::ArrayType>()
	{
		return to_ptr();
	}

	template<typename T, size_t N, size_t... NS> Array<T, N, NS...>::operator ArrayPtr<const Array::ArrayType>() const
	{
		return to_ptr();
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::operator[](size_t i) -> ArrayType&
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return _arr[i];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::operator[](size_t i) const -> const ArrayType&
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return _arr[i];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::begin() -> ArrayType*
	{
		return &_arr[0];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::begin() const -> const ArrayType*
	{
		return &_arr[0];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::end() -> ArrayType*
	{
		return &_arr[N];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::end() const -> const ArrayType*
	{
		return &_arr[N];
	}

	template<typename T, size_t N, size_t... NS> constexpr size_t Array<T, N, NS...>::size()
	{
		return N;
	}

	template<typename T, size_t N, size_t... NS> constexpr size_t Array<T, N, NS...>::flat_size()
	{
		return N * ArrayType::flat_size();
	}

	template<typename T, size_t N, size_t... NS> constexpr size_t Array<T, N, NS...>::sub_array_count()
	{
		return sizeof...(NS);
	}
}
// namespace::rcom
