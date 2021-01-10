#pragma once

#include "fundamental.hpp"
#include "assert.hpp"
#include <initializer_list>

namespace rcom
{
	// Multidimensional array
	template<typename T, size_t N, size_t... NS> class Array;

	template<typename T, size_t N> class Array<T, N>
	{
	public:
		template<typename... Ts> inline constexpr Array(Ts&&...);
	
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

	private:
		T arr[N];
	};

	template<typename T, size_t N> template<typename... Ts> constexpr Array<T, N>::Array(Ts&&... ts) :
		arr{ts...}
	{
	}
	
	template<typename T, size_t N> T& Array<T, N>::operator[](size_t i)
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return arr[i];
	}
	
	template<typename T, size_t N> const T& Array<T, N>::operator[](size_t i) const
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return arr[i];
	}
	
	template<typename T, size_t N> T* Array<T, N>::begin()
	{
		return &arr[0];
	}
	
	template<typename T, size_t N> const T* Array<T, N>::begin() const
	{
		return &arr[0];
	}
	
	template<typename T, size_t N> T* Array<T, N>::end()
	{
		return &arr[N];
	}
	
	template<typename T, size_t N> const T* Array<T, N>::end() const
	{
		return &arr[N];
	}
	
	template<typename T, size_t N> const T* Array<T, N>::data() const
	{
		return &arr[0];
	}
	
	template<typename T, size_t N> T* Array<T, N>::data()
	{
		return &arr[0];
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
		// Must be public for aggrigate initilisation
		typedef Array<T, NS...> ArrayType;

		inline constexpr Array(std::initializer_list<T>);
	
		inline       ArrayType&        operator[](size_t i);
		inline const ArrayType&        operator[](size_t i)   const;
		inline       ArrayType*        begin();
		inline const ArrayType*        begin()                const;
		inline       ArrayType*        end();
		inline const ArrayType*        end()                  const;
		inline       ArrayType*        data();
		inline const ArrayType*        data()                 const;

		// Multidimensional
		inline static constexpr size_t size();
		inline static constexpr size_t flat_size();
		inline static constexpr size_t sub_array_count();
	private:
		Array<ArrayType, N> arr;
	};


	template<typename T, size_t N, size_t... NS> constexpr Array<T, N, NS...>::Array(std::initializer_list<T> init) :
		arr{init}
	{
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::operator[](size_t i) -> ArrayType&
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return arr[i];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::operator[](size_t i) const -> const ArrayType&
	{
		RCOM_ASSERT(i < size(), "Index out of range");
		return arr[i];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::begin() -> ArrayType*
	{
		return &arr[0];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::begin() const -> const ArrayType*
	{
		return &arr[0];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::end() -> ArrayType*
	{
		return &arr[N];
	}

	template<typename T, size_t N, size_t... NS> auto Array<T, N, NS...>::end() const -> const ArrayType*
	{
		return &arr[N];
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
