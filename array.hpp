#pragma once

#include "array_ptr.hpp"
#include <initializer_list>

#define RCOM_ARRAY(TYPE, NAME, ...)        rcom::Array<TYPE, std::initializer_list<TYPE>__VA_ARGS__.size()> NAME{__VA_ARGS__}
#define RCOM_ARRAY_STRING(TYPE, NAME, ARR) rcom::Array<TYPE, RCOM_ARRAY_SIZE(ARR)> NAME{ARR}

namespace rcom
{
	// Multidimensional array
	template<typename T, size_t N, size_t... NS> class Array;

	template<typename T, size_t N> class Array<T, N>
	{
	public:
		static_assert(N > 0, "Array must be of non zero size");

		// Required to be an aggrigate
		// Do not access this directly. Use data() instead
		T _arr[N];

		constexpr static const size_t _flat_size = {N};
		constexpr static const size_t _byte_size = {_flat_size * sizeof(T)};

		Array()                        = default;
		Array(const Array&)            = default;
		Array(Array&&)                 = default;
		Array& operator=(const Array&) = default;
		Array& operator=(Array&&)      = default;
		~Array()                       = default;

		template<size_t NN = 0>
		inline static constexpr size_t size();
		inline static constexpr size_t byte_size();
		inline static constexpr size_t flat_size();

		inline       ArrayPtr<T> to_ptr();
		inline const ArrayPtr<T> to_ptr() const;
		inline       ArrayPtr<T> to_flat();
		inline const ArrayPtr<T> to_flat() const;
		inline       BytePtr     to_bytes();
		inline const BytePtr     to_bytes() const;

		inline const ArrayPtr<T> slice(size_t start, size_t end) const;
		inline       ArrayPtr<T> slice(size_t start, size_t end);
		inline const ArrayPtr<T> slice(size_t start) const;
		inline       ArrayPtr<T> slice(size_t start);

		inline const BytePtr byte_slice(size_t start, size_t end) const;
		inline       BytePtr byte_slice(size_t start, size_t end);
		inline const BytePtr byte_slice(size_t start) const;
		inline       BytePtr byte_slice(size_t start);

		inline constexpr       T& operator[](size_t i);
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
		return {_arr, N};
	}

	template<typename T, size_t N> const ArrayPtr<T> Array<T, N>::to_ptr() const
	{
		return {_arr, N};
	}

	template<typename T, size_t N> ArrayPtr<T> Array<T, N>::to_flat()
	{
		return {_arr, _flat_size};
	}

	template<typename T, size_t N> const ArrayPtr<T> Array<T, N>::to_flat() const
	{
		return {_arr, _flat_size};
	}

	template<typename T, size_t N> constexpr size_t Array<T, N>::byte_size()
	{
		return _byte_size;
	}

	template<typename T, size_t N> BytePtr Array<T, N>::to_bytes()
	{
		return {reinterpret_cast<uint8_t*>(_arr), _byte_size};
	}

	template<typename T, size_t N> const BytePtr Array<T, N>::to_bytes() const
	{
		return {reinterpret_cast<uint8_t*>(_arr), _byte_size};
	}

	template<typename T, size_t N> const ArrayPtr<T> Array<T, N>::slice(size_t start, size_t end) const
	{
		RCOM_ASSERT(start  > 0,   "Index out of range");
		RCOM_ASSERT(end    < N,   "Index out of range");
		RCOM_ASSERT(start  < end, "Invaid start and end points");

		return {&_arr[start], end - start};
	}

	template<typename T, size_t N> ArrayPtr<T> Array<T, N>::slice(size_t start, size_t end)
	{
		RCOM_ASSERT(start  > 0,   "Index out of range");
		RCOM_ASSERT(end    < N,   "Index out of range");
		RCOM_ASSERT(start  < end, "Invaid start and end points");

		return {&_arr[start], end - start};
	}

	template<typename T, size_t N> ArrayPtr<T> Array<T, N>::slice(size_t start)
	{
		return slice(start, N);
	}

	template<typename T, size_t N> ArrayPtr<T> const Array<T, N>::slice(size_t start) const
	{
		return slice(start, N);
	}

	template<typename T, size_t N> const BytePtr Array<T, N>::byte_slice(size_t start, size_t end) const
	{
		RCOM_ASSERT(start  > 0,   "Index out of range");
		RCOM_ASSERT(end    < N,   "Index out of range");
		RCOM_ASSERT(start  < end, "Invaid start and end points");

		return {reinterpret_cast<uint8_t*>(&_arr[start]), ::byte_size<T>(end - start)};
	}

	template<typename T, size_t N> BytePtr Array<T, N>::byte_slice(size_t start, size_t end)
	{
		RCOM_ASSERT(start  > 0,   "Index out of range");
		RCOM_ASSERT(end    < N,   "Index out of range");
		RCOM_ASSERT(start  < end, "Invaid start and end points");

		return {reinterpret_cast<uint8_t*>(&_arr[start]), ::byte_size<T>(end - start)};
	}

	template<typename T, size_t N> const BytePtr Array<T, N>::byte_slice(size_t start) const
	{
		return byte_slice(start, len);
	}

	template<typename T, size_t N> BytePtr Array<T, N>::byte_slice(size_t start)
	{
		return byte_slice(start, len);
	}

	template<typename T, size_t N> constexpr T& Array<T, N>::operator[](size_t i)
	{
		RCOM_ASSERT(i < N, "Index out of range");
		return _arr[i];
	}
	
	template<typename T, size_t N> constexpr const T& Array<T, N>::operator[](size_t i) const
	{
		RCOM_ASSERT(i < N, "Index out of range");
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

	template<typename T, size_t N>
	template<size_t NN> constexpr size_t Array<T, N>::size()
	{
		static_assert(NN < N, "Multidimensional array index out of range");
		return N;
	}

	// Multidimensional array
	template<typename T, size_t N, size_t... NS> class Array
	{
	public:
		static_assert(N > 0, "Array must be of non zero size");

		typedef Array<T, NS...> ArrayType;

		// Required to be an aggrigate
		// Use C array instead of Array due to indexing
		ArrayType _arr[N];

		// Sizes of each array available at compile time
		constexpr static const Array<size_t, 1 + sizeof...(NS)> _sizes{N, NS...};

		constexpr static const size_t _flat_size = sizeof(_arr) / sizeof(T);
		constexpr static const size_t _byte_size = _flat_size * sizeof(T);

		Array()                        = default;
		Array(const Array&)            = default;
		Array(Array&&)                 = default;
		Array& operator=(const Array&) = default;
		Array& operator=(Array&&)      = default;
		~Array()                       = default;

		template<size_t NN = 0>
		inline static constexpr size_t size();

		inline static constexpr size_t byte_size();
		inline static constexpr size_t flat_size();

		inline       ArrayPtr<ArrayType> to_ptr();
		inline const ArrayPtr<ArrayType> to_ptr() const;
		inline       ArrayPtr<T>         to_flat();
		inline const ArrayPtr<T>         to_flat() const;
		inline       BytePtr             to_bytes();
		inline const BytePtr             to_bytes() const;

		inline const ArrayPtr<ArrayType> slice(size_t start, size_t end) const;
		inline       ArrayPtr<ArrayType> slice(size_t start, size_t end);
		inline const ArrayPtr<ArrayType> slice(size_t start) const;
		inline       ArrayPtr<ArrayType> slice(size_t start);

		inline const BytePtr byte_slice(size_t start, size_t end) const;
		inline       BytePtr byte_slice(size_t start, size_t end);
		inline const BytePtr byte_slice(size_t start) const;
		inline       BytePtr byte_slice(size_t start);

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
		return {reinterpret_cast<uint8_t*>(_arr), _byte_size};
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::to_bytes() const -> const BytePtr
	{
		return {reinterpret_cast<uint8_t*>(_arr), _byte_size};
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::slice(size_t start, size_t end) const -> const ArrayPtr<ArrayType>
	{
		RCOM_ASSERT(start  > 0,     "Index out of range");
		RCOM_ASSERT(end    < _size, "Index out of range");
		RCOM_ASSERT(start  < end,   "Invaid start and end points");

		return {&_arr[start], end - start};
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::slice(size_t start, size_t end) -> ArrayPtr<ArrayType>
	{
		RCOM_ASSERT(start  > 0,     "Index out of range");
		RCOM_ASSERT(end    < _size, "Index out of range");
		RCOM_ASSERT(start  < end,   "Invaid start and end points");

		return {&_arr[start], end - start};
	}

	template<typename T, size_t N, size_t... NS> const BytePtr Array<T, N, NS...>::byte_slice(size_t start, size_t end) const
	{
		RCOM_ASSERT(start  > 0,     "Index out of range");
		RCOM_ASSERT(end    < _size, "Index out of range");
		RCOM_ASSERT(start  < end,   "Invaid start and end points");

		return {reinterpret_cast<uint8_t*>(&_arr[start]), ::byte_size<ArrayType>(end - start)};
	}

	template<typename T, size_t N, size_t... NS> BytePtr Array<T, N, NS...>::byte_slice(size_t start, size_t end)
	{
		RCOM_ASSERT(start  > 0,     "Index out of range");
		RCOM_ASSERT(end    < _size, "Index out of range");
		RCOM_ASSERT(start  < end,   "Invaid start and end points");

		return {reinterpret_cast<uint8_t*>(&_arr[start]), ::byte_size<ArrayType>(end - start)};
	}

	template<typename T, size_t N, size_t... NS> const BytePtr Array<T, N, NS...>::byte_slice(size_t start) const
	{
		return byte_slice(start, len);
	}

	template<typename T, size_t N, size_t... NS> BytePtr Array<T, N, NS...>::byte_slice(size_t start)
	{
		return byte_slice(start, len);
	}

	template<typename T, size_t N, size_t... NS> constexpr auto Array<T, N, NS...>::operator[](size_t i) -> ArrayType&
	{
		RCOM_ASSERT(i < N, "Index out of range");
		return _arr[i];
	}

	template<typename T, size_t N, size_t... NS> constexpr auto Array<T, N, NS...>::operator[](size_t i) const -> const ArrayType&
	{
		RCOM_ASSERT(i < N, "Index out of range");
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
		static_assert(NN < N, "Multidimensional array index out of range");
		return _sizes[NN];
	}

	template<typename T, size_t N, size_t... NS> constexpr size_t Array<T, N, NS...>::byte_size()
	{
		return _byte_size;
	}

	template<typename T, size_t N, size_t... NS> constexpr size_t Array<T, N, NS...>::flat_size()
	{
		return _flat_size;
	}

	template<typename T, size_t N, size_t... NS> ArrayPtr<T> Array<T, N, NS...>::to_flat()
	{
		return {reinterpret_cast<T*>(_arr), _flat_size};
	}

	template<typename T, size_t N, size_t... NS> const ArrayPtr<T> Array<T, N, NS...>::to_flat() const
	{
		return {reinterpret_cast<T*>(_arr), _flat_size};
	}
}
// namespace::rcom
