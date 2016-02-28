#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

template <typename T, size_t N>
class Array
{
	public:
		typedef T ValueType;
		typedef ValueType& Reference;
		typedef const ValueType& ConstReference;
		typedef ValueType* Pointer;
		typedef const ValueType* ConstPointer;
		typedef size_t SizeType;
		typedef ptrdiff_t DifferenceType;
		typedef T* Iterator;
		typedef const T* ConstIterator;

		/// Default constructor.
		Array();

		/// Constructs the array by copying \a value to each element in the
		/// array.
		/// \param value The value to copy.
		Array(const T& value);

		/// Constructs the array by giving args to the constructor of each
		/// element in the array.
		/// \param args The arguments to copy to the constructors.
		template <typename... Args>
		Array(const Args&... args);

		/// Destructor.
		~Array();

		Iterator begin();

		Iterator end();

		ConstIterator cbegin();

		ConstIterator cend();

		Reference operator[](SizeType pos);

		constexpr ConstReference operator[](SizeType pos) const;

		Reference at(SizeType pos);

		constexpr ConstReference at(SizeType pos) const;

		Reference front(SizeType pos);

		constexpr ConstReference front(SizeType pos) const;

		Reference back(SizeType pos);

		constexpr ConstReference back(SizeType pos) const;

		constexpr bool empty() const;

		constexpr SizeType size() const;

	private:
		char _array[N * sizeof(T)];
		T* _pointer{reinterpret_cast<T*>(&_array)};
};

template <typename T, size_t N>
Array<T, N>::Array():
	Array(T())
{
}

template <typename T, size_t N>
Array<T, N>::Array(const T& value)
{
	T* pointer{_pointer};
	for(size_t i{0}; i < N; ++i)
		// Construct in-place the elements
		new(pointer++) T(value);
}

template <typename T, size_t N>
template <typename... Args>
Array<T, N>::Array(const Args&... args)
{
	T* pointer{_pointer};
	for(size_t i{0}; i < N; ++i)
		new(pointer++) T(args...);
}

template <typename T, size_t N>
Array<T, N>::~Array()
{
	T* pointer{_pointer};
	for(size_t i{0}; i < N; ++i)
		(pointer++)->~T();
}

template <typename T, size_t N>
typename Array<T, N>::Iterator Array<T, N>::begin()
{
	return _pointer;
}

template <typename T, size_t N>
typename Array<T, N>::Iterator Array<T, N>::end()
{
	return _pointer + size();
}

template <typename T, size_t N>
typename Array<T, N>::ConstIterator Array<T, N>::cbegin()
{
	return _pointer;
}

template <typename T, size_t N>
typename Array<T, N>::ConstIterator Array<T, N>::cend()
{
	return _pointer + size();
}

template <typename T, size_t N>
typename Array<T, N>::Reference Array<T, N>::operator[](SizeType pos)
{
	return _pointer + size();
}

template <typename T, size_t N>
constexpr typename Array<T, N>::ConstReference Array<T, N>::operator[](SizeType pos) const
{
	return _pointer[pos];
}

template <typename T, size_t N>
typename Array<T, N>::Reference Array<T, N>::at(SizeType pos)
{
	return _pointer[pos];
}

template <typename T, size_t N>
constexpr typename Array<T, N>::ConstReference Array<T, N>::at(SizeType pos) const
{
	return _pointer[pos];
}

template <typename T, size_t N>
typename Array<T, N>::Reference Array<T, N>::front(SizeType pos)
{
	return _pointer[0];
}

template <typename T, size_t N>
constexpr typename Array<T, N>::ConstReference Array<T, N>::front(SizeType pos) const
{
	return _pointer[0];
}

template <typename T, size_t N>
typename Array<T, N>::Reference Array<T, N>::back(SizeType pos)
{
	return _pointer[size() - 1];
}

template <typename T, size_t N>
constexpr typename Array<T, N>::ConstReference Array<T, N>::back(SizeType pos) const
{
	return _pointer[size() - 1];
}

template <typename T, size_t N>
constexpr bool Array<T, N>::empty() const
{
	return size() == 0;
}

template <typename T, size_t N>
constexpr typename Array<T, N>::SizeType Array<T, N>::size() const
{
	return N;
}

#endif// ARRAY_HPP
