#ifndef STATIC_QUEUE_HPP
#define STATIC_QUEUE_HPP

#include <std/cstddef>
#include <cpp/utility.hpp>
#include <cpp/math.hpp>
#include <cpp/assert.hpp>

template <class T, size_t MaxSize>
class StaticQueue
{
	private:
		template <class T_, size_t MaxSize_>
		class StaticQueueIterator
		{
			public:
				/// Constructor from list node.
				/// \param queue The iterated queue.
				/// \param index The iteration index of this iterator.
				explicit StaticQueueIterator(StaticQueue<T_, MaxSize_>& queue, size_t index);

				/// Dereferencement operator.
				/// \return A reference to the pointed object.
				T_& operator*() const;

				/// Dereferencement operator.
				/// \return A pointer to the pointed object.
				T_* operator->() const;

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
				StaticQueue<T_, MaxSize_>& _queue; ///< The iterated queue.
				size_t _index; ///< The iteration index of this iterator.

				friend class StaticQueue;
		};

	public:
		typedef StaticQueueIterator<T, MaxSize> Iterator; ///< Non constant iterator.
		typedef StaticQueueIterator<const T, MaxSize> ConstIterator;///< Constant iterator.

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
	return _data[_last - 1];
}

template <class T, size_t MaxSize>
const T& StaticQueue<T, MaxSize>::back() const
{
	return _data[_last - 1];
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
	_size = math::max(0ul, _size - 1);
	// If, for some reason, _size was zero and has been decremented
	if(_size > MaxSize)
		_size = 0;
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
	_size = math::min(MaxSize, _size + 1);
	return oldLast;
}

#endif // STATIC_QUEUE_HPP
