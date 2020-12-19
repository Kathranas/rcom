#pragma once

#include <initializer_list>

namespace rcom
{
	template<typename T, size_t N> class Array
	{
	public:
		inline Array() = default;
		inline constexpr Array(T(&)[N]);

		template<typename... Ts> inline constexpr Array(Ts... ts);
	
		inline       T&  operator[](size_t i);
		inline const T&  operator[](size_t i)   const;
		inline       T*  begin();
		inline const T*  begin()                const;
		inline       T*  end();
		inline const T*  end()                  const;
		inline       T*  data();
		inline const T*  data()                 const;
		inline constexpr size_t size()          const;
	private:
		T arr[N];
	};
	
	template<typename T, size_t N> constexpr Array<T, N>::Array(T(&t)[N])
		: arr{t}
	{
	}
	
//	template<typename T, size_t N> constexpr Array<T, N>::Array(std::initializer_list<T> temp)
//		: arr{temp}
//	{
//	}
	
	template<typename T, size_t N> T& Array<T, N>::operator[](size_t i)
	{
		return arr[i];
	}
	
	template<typename T, size_t N> const T& Array<T, N>::operator[](size_t i) const
	{
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
	
	template<typename T, size_t N> constexpr size_t Array<T, N>::size() const
	{
		return N;
	}


	template<typename T, size_t N> template<typename... Ts> constexpr Array<T, N>::Array(Ts... ts) :
		arr{ts...}
	{
	}
}
// namespace::rcom
