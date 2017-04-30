#ifndef INITIALIZERLIST_HPP
#define INITIALIZERLIST_HPP

#include <std/cstddef>

/// \addtogroup Cpp
/// \{

/// Initializer list class helper. This class behaves like std::initialize_list,
/// and is part of the pseudo-implementation of the standard C++ library.
/// This class is directly copied from the implementation of
/// std::initializer_list given in GNU g++-5.2, with adapted naming conventions.
/// \tparam T The type of element.
template<class T>
class InitializerList
{
	public:
		typedef T ValueType;            ///< Contained value type.
		typedef const T& Reference;     ///< Reference to value type.
		typedef const T& ConstReference;///< Const reference.
		typedef size_t SizeType;        ///< The type of the size.
		typedef const T* Iterator;      ///< Iterator type.
		typedef const T* ConstIterator; ///< Const iterator type.

		/// Default constructor.
		/// \post begin() == end().
		constexpr InitializerList() noexcept;


		/// Gets the number of elements.
		/// \return The number of elements.
		constexpr SizeType size() const noexcept;

		/// Gets the first element.
		/// \return The first element.
		constexpr ConstIterator begin() const noexcept;

		/// Gets the past the last element.
		/// \return The past the last element.
		constexpr ConstIterator end() const noexcept;

	private:
		/// Constructor. The compiler can call a private constructor.
		/// \param array An iterator (i.e. a pointer) to the data.
		/// \param length The number of elements.
		constexpr InitializerList(ConstIterator array, SizeType length);

		Iterator _array; ///< Pointer to the underlying data.
		SizeType _length;///< Number of elements.
};

/// \brief Returns an Iterator pointing to the first element of
/// the InitializerList.
/// \param initializerList Initializer list.
/// \tparam T The type of element.
template<class T>
constexpr const typename InitializerList<T>::Iterator begin(InitializerList<T> initializerList) noexcept;

/// \brief Returns an Iterator pointing to one past the last element
/// of the InitializerList.
/// \param initializerList Initializer list.
/// \tparam T The type of element.
template<class T>
constexpr const typename InitializerList<T>::Iterator end(InitializerList<T> initializerList) noexcept;

/// \}

template<class T>
constexpr InitializerList<T>::InitializerList(ConstIterator array, SizeType length):
	_array(array),
	_length(length)
{
}

template<class T>
constexpr InitializerList<T>::InitializerList() noexcept:
	_array(nullptr), _length(0)
{
}

template<class T>
constexpr typename InitializerList<T>::SizeType InitializerList<T>::size() const noexcept
{
	return _length;
}

template<class T>
constexpr typename InitializerList<T>::ConstIterator InitializerList<T>::begin() const noexcept
{
	return _array;
}

template<class T>
constexpr typename InitializerList<T>::ConstIterator InitializerList<T>::end() const noexcept
{
	return begin() + size();
}

template<class T>
constexpr const typename InitializerList<T>::Iterator begin(InitializerList<T> initializerList) noexcept
{
	return initializerList.begin();
}

template<class T>
constexpr const typename InitializerList<T>::Iterator end(InitializerList<T> initializerList) noexcept
{
	return initializerList.end();
}

#endif// INITIALIZERLIST_HPP
