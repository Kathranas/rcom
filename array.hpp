#pragma once

#include "fundamental.hpp"
#include "assert.hpp"
#include "array_ptr.hpp"
#include <initializer_list>

#define RCOM_ARRAY_SIZE(ARR) (sizeof(ARR) / sizeof(*ARR))

#define RCOM_MAKE_ARRAY(NAME, TYPE, ...)  rcom::Array<TYPE, std::initializer_list<TYPE>__VA_ARGS__.size()> NAME{__VA_ARGS__}
#define RCOM_FROM_STRING(NAME, TYPE, ARR) rcom::Array<TYPE, RCOM_ARRAY_SIZE(ARR)> NAME{ARR}

namespace rcom
{
	// Multidimensional array
	template<typename T, size_t N, size_t... NS> class Array;

	template<typename T, size_t N> class Array<T, N>
	{
	public:
		// Required to be an aggrigate
		T _arr[N]; // Do not access this directly. Use data() instead

		Array()                        = default;
		Array(const Array&)            = default;
		Array(Array&&)                 = default;

		Array& operator=(const Array&) = default;
		Array& operator=(Array&&)      = default;
		~Array()                       = default;

		inline static constexpr size_t size();
		inline static constexpr size_t byte_size();

		inline       ArrayPtr<T> to_ptr();
		inline const ArrayPtr<T> to_ptr() const;

		inline       BytePtr to_bytes();
		inline const BytePtr to_bytes() const;

		inline constexpr      T& operator[](size_t i);
		inline constexpr const T& operator[](size_t i) const;

		inline       T* data();
		inline const T* data()   const;
		inline       T* begin();
		inline const T* begin()  const;
		inline       T* end();
		inline const T* end()    const;
		inline       T& first();
		inline const T& first()  const;
		inline       T& last();
		inline const T& last()   const;
	};

	template<typename T, size_t N> ArrayPtr<T> Array<T, N>::to_ptr()
	{
		return {data(), N};
	}

	template<typename T, size_t N> const ArrayPtr<T> Array<T, N>::to_ptr() const
	{
		return {data(), N};
	}

	template<typename T, size_t N> constexpr size_t Array<T, N>::byte_size()
	{
		return N * sizeof(T);
	}

	template<typename T, size_t N> BytePtr Array<T, N>::to_bytes()
	{
		return {static_cast<uint8_t*>((void*)data()), byte_size()};
	}

	template<typename T, size_t N> const BytePtr Array<T, N>::to_bytes() const
	{
		return {static_cast<uint8_t*>((void*)data()), byte_size()};
	}

	template<typename T, size_t N> constexpr T& Array<T, N>::operator[](size_t i)
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return _arr[i];
	}
	
	template<typename T, size_t N> constexpr const T& Array<T, N>::operator[](size_t i) const
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

	template<typename T, size_t N> T& Array<T, N>::first()
	{
		return _arr[0];
	}

	template<typename T, size_t N> const T& Array<T, N>::first() const
	{
		return _arr[0];
	}

	template<typename T, size_t N> T& Array<T, N>::last()
	{
		return _arr[N-1];
	}

	template<typename T, size_t N> const T& Array<T, N>::last() const
	{
		return _arr[N-1];
	}
	
	template<typename T, size_t N> constexpr size_t Array<T, N>::size()
	{
		return N;
	}

	// Multidimensional array
	template<typename T, size_t N, size_t... NS> class Array
	{
	public:
		typedef Array<T, NS...> ArrayType;

		// Required to be an aggrigate
		// Use C array instead of Array due to indexing
		ArrayType _arr[N];

		// Sizes of each array available at compile time
		constexpr static const Array<size_t, 1 + sizeof...(NS)> _sizes{N, NS...};

		Array()                        = default;
		Array(const Array&)            = default;
		Array(Array&&)                 = default;

		Array& operator=(const Array&) = default;
		Array& operator=(Array&&)      = default;
		~Array()                       = default;

		// Multidimensional
		template<size_t NN = 0>
		inline static constexpr size_t size();
		inline static constexpr size_t byte_size();

		inline       ArrayPtr<ArrayType> to_ptr();
		inline const ArrayPtr<ArrayType> to_ptr() const;
		inline       BytePtr             to_bytes();
		inline const BytePtr             to_bytes() const;

		inline constexpr       ArrayType& operator[](size_t i);
		inline constexpr const ArrayType& operator[](size_t i)  const;

		inline       ArrayType* data();
		inline const ArrayType* data()   const;
		inline       ArrayType* begin();
		inline const ArrayType* begin()  const;
		inline       ArrayType* end();
		inline const ArrayType* end()    const;
		inline       ArrayType& first();
		inline const ArrayType& first()  const;
		inline       ArrayType& last();
		inline const ArrayType& last()   const;
	};

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::to_ptr() -> ArrayPtr<ArrayType>
	{
		return {_arr, N};
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::to_ptr() const -> const ArrayPtr<ArrayType>
	{
		return {_arr, N};
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::to_bytes() -> BytePtr
	{
		return {static_cast<uint8_t*>((void*)data()), byte_size()};
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::to_bytes() const -> const BytePtr
	{
		return {static_cast<uint8_t*>((void*)data()), byte_size()};
	}

	template<typename T, size_t N, size_t... NS> constexpr auto Array<T, N, NS...>::operator[](size_t i) -> ArrayType&
	{
		return _arr[i];
	}

	template<typename T, size_t N, size_t... NS> constexpr auto Array<T, N, NS...>::operator[](size_t i) const -> const ArrayType&
	{
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

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::first() -> ArrayType&
	{
		return _arr[N];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::first() const -> const ArrayType&
	{
		return _arr[N];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::last() -> ArrayType&
	{
		return _arr[N-1];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::last() const -> const ArrayType&
	{
		return _arr[N-1];
	}

	template<typename T, size_t N, size_t... NS>
	template<size_t NN> constexpr size_t Array<T, N, NS...>::size()
	{
		return _sizes[NN];
	}

	template<typename T, size_t N, size_t... NS> constexpr size_t Array<T, N, NS...>::byte_size()
	{
		return size() * sizeof(T);
	}
}
// namespace::rcom
