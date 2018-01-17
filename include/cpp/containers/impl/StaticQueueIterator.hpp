#ifndef STATIC_QUEUE_ITERATOR_HPP
#define STATIC_QUEUE_ITERATOR_HPP

#include <std/cstddef>

namespace impl
{

template <class T, size_t MaxSize>
class StaticQueueIterator
{
	public:
		/// Constructor from list node.
		/// \param array The array to iterate.
		/// \param index The index of the pointed element.
		explicit StaticQueueIterator(T* array, size_t index);

		/// Dereferencement operator.
		/// \return A reference to the pointed object.
		T& operator*() const;

		/// Dereferencement operator.
		/// \return A pointer to the pointed object.
		T* operator->() const;

		/// Increment operator. This advances the iterator by one
		/// element.
		/// \return A reference to the advanced iterator.
		StaticQueueIterator& operator++();

		/// Increment operator. This advances the iterator by one
		/// element.
		/// \return The old, non advanced iterator.
		StaticQueueIterator operator++(int);

		/// Decrement operator. This moves the iterator by one
		/// element back.
		/// \return A reference to the moved iterator.
		StaticQueueIterator& operator--();

		/// Decrement operator. This moves the iterator by one
		/// element back.
		/// \return The old, non advanced iterator.
		StaticQueueIterator operator--(int);

		/// Comparison operator.
		/// \param other The other iterator to compare to.
		/// \return True if the iterators point to the same node, false
		/// otherwhise.
		bool operator==(const StaticQueueIterator& other) const;

		/// Comparison operator.
		/// \param other The other iterator to compare to.
		/// \return True if the iterators do not point to the same node,
		/// false otherwhise.
		bool operator!=(const StaticQueueIterator& other) const;

	private:
		T* _array; ///< The iterated buffer.
		size_t _index; ///< The index of the pointed element.
};

} // namespace impl

namespace impl
{

template <class T, size_t MaxSize>
StaticQueueIterator<T, MaxSize>::StaticQueueIterator(T* array, size_t index):
	_array{array},
	_index{index}
{
}

template <class T, size_t MaxSize>
T&  StaticQueueIterator<T, MaxSize>::operator*() const
{
	return _array[_index];
}

template <class T, size_t MaxSize>
T*  StaticQueueIterator<T, MaxSize>::operator->() const
{
	return &operator*(*this);
}

template <class T, size_t MaxSize>
StaticQueueIterator<T, MaxSize>& StaticQueueIterator<T, MaxSize>::operator++()
{
	_index = (_index + 1) % MaxSize;
	return *this;
}

template <class T, size_t MaxSize>
StaticQueueIterator<T, MaxSize> StaticQueueIterator<T, MaxSize>::operator++(int)
{
	StaticQueueIterator tmp{*this};
	operator++();
	return tmp;
}

template <class T, size_t MaxSize>
bool StaticQueueIterator<T, MaxSize>::operator==(const StaticQueueIterator<T, MaxSize>& other) const
{
	return _array == other._array and _index == other._index;
}

template <class T, size_t MaxSize>
bool StaticQueueIterator<T, MaxSize>::operator!=(const StaticQueueIterator<T, MaxSize>& other) const
{
	return not (*this == other);
}

} // namespace impl

#endif // STATIC_QUEUE_ITERATOR_HPP
