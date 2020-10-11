#include "array_ptr.hpp"

template<typename T> class DynamicArray
{
public:
	inline DynamicArray();
	inline DynamicArray(std::nullptr_t);
	inline DynamicArray(T* t, size_t n, size_t c = 0);
	template<size_t N>
	inline DynamicArray(T(&t)[N], size_t c = 0);
	inline operator DynamicArray<const T>() const;
	inline operator bool()                  const;

	inline       T&  operator[](size_t i);
	inline const T&  operator[](size_t i)   const;
	inline       T*  begin();
	inline const T*  begin()                const;
	inline       T*  end();
	inline const T*  end()                  const;
	inline       T*& data();
	inline const T*  data()                 const;
	inline size_t&   size();
	inline size_t    size()                 const;

	inline void    push_back(const T&);
	inline void    push_back(T&&);
	inline void    pop_back();
	inline size_t  count() const;
private:
	T*     data_ptr;
	size_t data_size;
	size_t data_count;
};

template<typename T> DynamicArray<T>::DynamicArray()
	: DynamicArray{nullptr}
{
}

template<typename T> DynamicArray<T>::DynamicArray(std::nullptr_t) 
	: data_ptr{nullptr}, data_size{0}, data_count{0}
{
}

template<typename T> DynamicArray<T>::DynamicArray(T* t, size_t n, size_t c) 
	: data_ptr{t}, data_size{n}, data_count{c}
{
}

template<typename T> template<size_t N> DynamicArray<T>::DynamicArray(T(&t)[N], size_t c) 
	: DynamicArray{t, N, c}
{
}

template<typename T> DynamicArray<T>::operator DynamicArray<const T>() const
{
	return {data_ptr, data_size, data_count};
}

template<typename T> DynamicArray<T>::operator bool() const
{
	return data_ptr;
}

template<typename T> void DynamicArray<T>::push_back(const T& t)
{
	data_ptr[data_count++] = t;
}

template<typename T> void DynamicArray<T>::push_back(T&& t)
{
	data_ptr[data_count++] = std::move(t);
}

template<typename T> void DynamicArray<T>::pop_back()
{
	if(count > 0)
	{
		count--;
	}
}

template<typename T> size_t DynamicArray<T>::count() const
{
	return data_count;
}

template<typename T> T& DynamicArray<T>::operator[](size_t i)
{
	return data_ptr[i];
}

template<typename T> const T& DynamicArray<T>::operator[](size_t i) const
{
	return data_ptr[i];
}
 
template<typename T> T* DynamicArray<T>::begin()
{
	return data_ptr;
}

template<typename T> const T* DynamicArray<T>::begin() const 
{
	return data_ptr;
}

template<typename T> T* DynamicArray<T>::end()
{
	return data_ptr + data_count;
}

template<typename T> const T* DynamicArray<T>::end() const
{
	return data_ptr + data_count;
}

template<typename T> T*& DynamicArray<T>::data()
{
	return data_ptr;
}

template<typename T> const T* DynamicArray<T>::data() const
{
	return data_ptr;
}

template<typename T> size_t& DynamicArray<T>::size()
{
	return data_size;
}

template<typename T> size_t  DynamicArray<T>::size() const
{
	return data_size;
}

template<typename T> inline ArrayPtr<T> to_ptr(DynamicArray<T> arr)
{
	return {arr.data(), arr.count()};
}
