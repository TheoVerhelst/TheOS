#ifndef STATIC_QUEUE_HPP
#define STATIC_QUEUE_HPP

#include <std/cstddef>
#include <cpp/utility.hpp>
#include <cpp/assert.hpp>
#include <cpp/containers/impl/StaticQueueIterator.hpp>

/// Implements a queue of static size using a circular buffer. This is useful
/// for having a queueing behavior without dynamic allocation. MaxSize is the
/// maximum number of elements in the queue. If more than MaxSize elements are
/// pushed, the oldest ones are discarded and written over. Note that for the
/// sake of a safer and simpler implementation, only MaxSize - 1 slots are
/// effectively available for storage.
///
/// Since the storage is static, the object are constructed once at the
/// StaticQueue creation, and destroyed at the StaticQueue destruction. The
/// pushBack function uses assignment operator, and popFront does not make any
/// copy. It is therefore the user responsability to copy the instance before it
/// is overwritten when the buffer cycles.
template <class T, size_t MaxSize>
class StaticQueue
{
	public:
		typedef impl::StaticQueueIterator<T, MaxSize> Iterator; ///< Non constant iterator.
		typedef impl::StaticQueueIterator<const T, MaxSize> ConstIterator;///< Constant iterator.

		/// Checks if the queue is empty.
		/// \return size() == 0.
		bool empty() const;

		/// Gets the number of elements in the queue.
		/// \return The number of elements in the queue.
		size_t size() const;

		/// Gets the last element of the queue.
		/// \pre not empty().
		/// \return The last element of the queue.
		T& back();

		/// Gets the last element of the queue.
		/// \pre not empty().
		/// \return The last element of the queue.
		const T& back() const;

		/// Gets the first element of the queue.
		/// \pre not empty().
		/// \return The first element of the queue.
		T& front();

		/// Gets the first element of the queue.
		/// \pre not empty().
		/// \return The first element of the queue.
		const T& front() const;

		/// Erases all elements of the queue/
		/// \post empty().
		void clear();

		/// Adds an element at the end of the queue, by copying it. If the queue
		/// has reached is maximum capacity, the first element is erased.
		/// \param value The value to add to the queue.
		/// \post not empty().
		void pushBack(const T& value);

		/// Adds an element at the end of the queue, by moving it. If the queue
		/// has reached is maximum capacity, the first element is erased.
		/// \param value The value to add to the queue.
		/// \post not empty().
		void pushBack(T&& value);

		/// Returns the first element of the queue. Its destructor is not
		/// called, since the storage is static. The object stays in memory as
		/// long as another object is not assigned to this slot.
		/// \pre not empty().
		/// \return The removed element.
		T& popFront();

		/// Returns the first element of the queue. Its destructor is not
		/// called, since the storage is static. The object stays in memory as
		/// long as another object is not assigned to this slot.
		/// \pre not empty().
		/// \return The removed element.
		const T& popFront() const;

		/// Gets an iterator to the first element of the queue.
		/// \return An iterator to the first element of the queue.
		Iterator begin();

		/// Gets a constant iterator to the first element of the queue.
		/// \return A constant iterator to the first element of the queue.
		ConstIterator begin() const;

		/// Gets an iterator to the past the last element of the queue.
		/// \return An iterator to the past the last element of the queue.
		Iterator end();

		/// Gets a constant iterator to the past the last element of the queue.
		/// \return A constant iterator to the past the last element of the
		/// list.
		ConstIterator end() const;

	private:
		/// Common code between the two versions of pushBack.
		/// \return The index to which assign the new value.
		size_t pushBackImpl();

		/// The index of first element of the queue.
		size_t _first{0};

		/// The index of last element of the queue.
		size_t _last{0};

		/// The number of elements in the queue.
		size_t _size{0};

		/// The internal, actual buffer.
		T _data[MaxSize];
};

template <class T, size_t MaxSize>
bool StaticQueue<T, MaxSize>::empty() const
{
	return size() == 0;
}

template <class T, size_t MaxSize>
size_t StaticQueue<T, MaxSize>::size() const
{
	return _size;
}

template <class T, size_t MaxSize>
T& StaticQueue<T, MaxSize>::back()
{
	return _data[(_last + MaxSize - 1) % MaxSize];
}

template <class T, size_t MaxSize>
const T& StaticQueue<T, MaxSize>::back() const
{
	return _data[(_last + MaxSize - 1) % MaxSize];
}

template <class T, size_t MaxSize>
T& StaticQueue<T, MaxSize>::front()
{
	return _data[_first];
}

template <class T, size_t MaxSize>
const T& StaticQueue<T, MaxSize>::front() const
{
	return _data[_first];
}

template <class T, size_t MaxSize>
void StaticQueue<T, MaxSize>::clear()
{
	_first = 0;
	_last = 0;
	_size = 0;
}

template <class T, size_t MaxSize>
void StaticQueue<T, MaxSize>::pushBack(const T& value)
{
	_data[pushBackImpl()] = value;
}

template <class T, size_t MaxSize>
void StaticQueue<T, MaxSize>::pushBack(T&& value)
{
	_data[pushBackImpl()] = forward<T>(value);
}

template <class T, size_t MaxSize>
T& StaticQueue<T, MaxSize>::popFront()
{
	ASSERT(_first != _last);
	size_t oldFirst{_first};
	_first = (_first + 1) % MaxSize;
	// If, for some reason, _size is zero (shouldn't with the assert though)
	if(_size == 0)
		// Avoid for _first to go past _last, that would be bad
		_last = _first;
	else
		_size -= 1;
	return _data[oldFirst];
}

template <class T, size_t MaxSize>
const T& StaticQueue<T, MaxSize>::popFront() const
{
	return const_cast<StaticQueue<T, MaxSize>&>(*this).popFront();
}


template <class T, size_t MaxSize>
size_t StaticQueue<T, MaxSize>::pushBackImpl()
{
	size_t oldLast{_last};
	_last = (_last + 1) % MaxSize;
	// If there is not enough space, eat the cell of the first element
	if(_size >= MaxSize - 1)
		// Avoid for _last to go past _first, that would be bad
		_first = (_first + 1) % MaxSize;
	else
		_size += 1;
	return oldLast;
}

template <class T, size_t MaxSize>
typename StaticQueue<T, MaxSize>::Iterator StaticQueue<T, MaxSize>::begin()
{
	return Iterator(_data, _first);
}

template <class T, size_t MaxSize>
typename StaticQueue<T, MaxSize>::ConstIterator StaticQueue<T, MaxSize>::begin() const
{
	return ConstIterator(_data, _first);
}

template <class T, size_t MaxSize>
typename StaticQueue<T, MaxSize>::Iterator StaticQueue<T, MaxSize>::end()
{
	return Iterator(_data, _last);
}

template <class T, size_t MaxSize>
typename StaticQueue<T, MaxSize>::ConstIterator StaticQueue<T, MaxSize>::end() const
{
	return ConstIterator(_data, _last);
}

#endif // STATIC_QUEUE_HPP
