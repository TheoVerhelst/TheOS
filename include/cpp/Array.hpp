#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <std/cstddef>
#include <cpp/new.hpp>

/// \defgroup Cpp C++
/// Pseudo-implementation of the standard C++ library.
/// \{

/// Static array encapsulated in a class. This class behaves like std::array,
/// and is part of the pseudo-implementation of the standard C++ library.
/// A great difference with std::array and with C-style array is that this
/// class allows to pass an argument to the constructor of the contained
/// elements, thus the elements of the array do not need to be
/// default-constructible. This is implemented with an array of bytes rather
/// than an array of \a T, and by constructing elements in place.
/// \tparam T The type of element.
/// \tparam N The number of elements.
template <typename T, size_t N>
class Array
{
	public:
		typedef T ValueType;                    ///< Contained value type.
		typedef ValueType& Reference;           ///< Reference to value type.
		typedef const ValueType& ConstReference;///< Const reference.
		typedef ValueType* Pointer;             ///< Pointer to value type.
		typedef const ValueType* ConstPointer;  ///< Const pointer.
		typedef size_t SizeType;                ///< The type of the size.
		typedef ptrdiff_t DifferenceType;       ///< The type used for indexing.
		typedef T* Iterator;                    ///< Iterator type.
		typedef const T* ConstIterator;         ///< Const iterator type.

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
		Array(Args&... args);

		/// Destructor.
		~Array();

		/// Gets an iterator to the first element of the array.
		/// \return An iterator to the first element of the array.
		Iterator begin();

		/// Gets an iterator to the past-the-end element of the array.
		/// \return An iterator to the past-the-end element of the array.
		Iterator end();

		/// Gets a constant iterator to the first element of the array.
		/// \return A constant iterator to the first element of the array.
		ConstIterator cbegin();

		/// Gets a constant iterator to the past-the-end element of the array.
		/// \return A constant iterator to the past-the-end element of the
		/// array.
		ConstIterator cend();

		/// Accesses the array at position \a pos.
		/// \param pos The position of the element to access.
		/// \return at(pos)
		Reference operator[](SizeType pos);

		/// Accesses the array at position \a pos.
		/// \param pos The position of the element to access.
		/// \return at(pos)
		constexpr ConstReference operator[](SizeType pos) const;

		/// Accesses the array at position \a pos.
		/// \param pos The position of the element to access.
		/// \return The element at position \a pos.
		Reference at(SizeType pos);

		/// Accesses the array at position \a pos.
		/// \param pos The position of the element to access.
		/// \return The element at position \a pos.
		constexpr ConstReference at(SizeType pos) const;

		/// Accesses the first element of the array.
		/// \pre not empty()
		/// \return at(0)
		Reference front();

		/// Accesses the first element of the array.
		/// \pre not empty()
		/// \return at(0)
		constexpr ConstReference front() const;

		/// Accesses the last element of the array.
		/// \pre not empty()
		/// \return at(size() - 1)
		Reference back();

		/// Accesses the last element of the array.
		/// \pre not empty()
		/// \return at(size() - 1)
		constexpr ConstReference back() const;

		/// Checks whether the array is empty, i.e. if its template parameter
		/// \a N is equal to 0.
		/// \return size() > 0
		constexpr bool empty() const;

		/// Gets the size of the array.
		/// \return N
		constexpr SizeType size() const;

	private:
		char _array[N * sizeof(T)];
		T* const _pointer{reinterpret_cast<T*>(&_array)};
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
		new (pointer++) T(value);
}

template <typename T, size_t N>
template <typename... Args>
Array<T, N>::Array(Args&... args)
{
	T* pointer{_pointer};
	for(size_t i{0}; i < N; ++i)
		new (pointer++) T(args...);
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
	return _pointer[pos];
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
typename Array<T, N>::Reference Array<T, N>::front()
{
	return _pointer[0];
}

template <typename T, size_t N>
constexpr typename Array<T, N>::ConstReference Array<T, N>::front() const
{
	return _pointer[0];
}

template <typename T, size_t N>
typename Array<T, N>::Reference Array<T, N>::back()
{
	return _pointer[size() - 1];
}

template <typename T, size_t N>
constexpr typename Array<T, N>::ConstReference Array<T, N>::back() const
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



#endif // ARRAY_HPP
