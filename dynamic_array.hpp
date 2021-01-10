#pragma once

#include "fundamental.hpp"
#include "assert.hpp"

namespace rcom
{
	template<typename T, size_t N> class DynamicArray
	{
	public:
		template<typename... Ts> inline constexpr DynamicArray(Ts&&...);

		inline operator DynamicArray<const T, N>() const;
	
		inline       T&  operator[](size_t i);
		inline const T&  operator[](size_t i)   const;
		inline       T*  begin();
		inline const T*  begin()                const;
		inline       T*  end();
		inline const T*  end()                  const;
		inline       T*& data();
		inline const T*  data()                 const;
		inline size_t    size()                 const;
		inline size_t&   count();
		inline size_t    count()                const;
	private:
		T      arr[N];
		size_t num;
	};

	template<typename T, size_t N> template<typename... Ts> constexpr DynamicArray<T, N>::DynamicArray(Ts&&... ts) :
		arr{ts...},
		num{sizeof...(Ts)}
	{
	}

	template<typename T, size_t N> DynamicArray<T, N>::operator DynamicArray<const T, N>() const
	{
		return {arr, N, num};
	}
	
	template<typename T, size_t N> size_t& DynamicArray<T, N>::count()
	{
		return num;
	}
	
	template<typename T, size_t N> size_t DynamicArray<T, N>::count() const
	{
		return num;
	}
	
	template<typename T, size_t N> T& DynamicArray<T, N>::operator[](size_t i)
	{
		RCOM_ASSERT(i < count(), "Index out of range");
		return arr[i];
	}
	
	template<typename T, size_t N> const T& DynamicArray<T, N>::operator[](size_t i) const
	{
		RCOM_ASSERT(i < count(), "Index out of range");
		return arr[i];
	}
	 
	template<typename T, size_t N> T* DynamicArray<T, N>::begin()
	{
		return arr;
	}
	
	template<typename T, size_t N> const T* DynamicArray<T, N>::begin() const
	{
		return arr;
	}
	
	template<typename T, size_t N> T* DynamicArray<T, N>::end()
	{
		// End of logical array rather than end of capacity
		return &arr[num];
	}
	
	template<typename T, size_t N> const T* DynamicArray<T, N>::end() const
	{
		return &arr[num];
	}
	
	template<typename T, size_t N> T*& DynamicArray<T, N>::data()
	{
		return arr;
	}
	
	template<typename T, size_t N> const T* DynamicArray<T, N>::data() const
	{
		return arr;
	}
	
	template<typename T, size_t N> size_t  DynamicArray<T, N>::size() const
	{
		return N;
	}
}
// namespace rcom
