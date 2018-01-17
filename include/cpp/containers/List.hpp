#ifndef LIST_HPP
#define LIST_HPP

#include <std/cstddef>
#include <cpp/utility.hpp>
#include <cpp/allocators/Allocator.hpp>
#include <cpp/containers/impl/Node.hpp>

/// Dynamic double-linked list. This class has approximatively the same
/// interface as `std::list`, and is part of the pseudo-implementation of the
/// standard C++ library.
///
/// This class can be used with a custom allocator, which is useful when the
/// memory have to be used in a certain manner (e.g. when the operator new is
/// not yet available).
/// \tparam T The type of element.
/// \tparam Allocator<T> The type of allocator to use.
template <class T>
class List
{
	public:
		typedef impl::ListNode<T> NodeType;
		typedef NodeType ToAllocate; ///< The type that should be managed by the allocator.
		typedef impl::NodeIterator<T, NodeType> Iterator; ///< Non constant iterator.
		typedef impl::NodeIterator<const T, const NodeType> ConstIterator;///< Constant iterator.

		/// Constructor.
		/// \param allocator The allocator to use.
		List(Allocator<NodeType>& allocator = Allocator<NodeType>::getDefault());

		/// Copy constructor.
		/// \param other The other list to copy.
		List(const List& other);

		/// Move constructor.
		/// \param other The other list.
		List(List&& other);

		/// Destructor.
		~List();

		/// Copy assignment operator.
		/// \param other The other list to copy.
		/// \return *this.
		List& operator=(List other);

		/// Checks if the list is empty.
		/// \return begin() == end().
		bool empty() const;

		/// Gets the number of elements in the list.
		/// \return The number of elements in the list.
		size_t size() const;

		/// Gets the last element of the list.
		/// \pre not empty().
		/// \return The last element of the list.
		T& back();

		/// Gets the last element of the list.
		/// \pre not empty().
		/// \return The last element of the list.
		const T& back() const;

		/// Gets the first element of the list.
		/// \pre not empty().
		/// \return The first element of the list.
		T& front();

		/// Gets the first element of the list.
		/// \pre not empty().
		/// \return The first element of the list.
		const T& front() const;

		/// Erases all elements of the list, this is equivalent to
		/// erase(begin(), end()).
		/// \post empty().
		void clear();

		/// Adds an element at the end of the list, by copying it.
		/// \param value The value to add to the list.
		/// \post not empty().
		void pushBack(const T& value);

		/// Adds an element at the end of the list, by moving it.
		/// \param value The value to add to the list.
		/// \post not empty().
		void pushBack(T&& value);

		/// Adds an element at the begin of the list, by moving it.
		/// \param value The value to add to the list.
		/// \post not empty().
		void pushFront(const T& value);

		/// Adds an element at the begin of the list, by moving it.
		/// \param value The value to add to the list.
		/// \post not empty().
		void pushFront(T&& value);

		/// Removes the last element of the list.
		/// \pre not empty().
		/// \return The removed element.
		T popBack();

		/// Removes the last element of the list.
		/// \pre not empty().
		/// \return The removed element.
		T popFront();

		/// Gets an iterator to the first element of the list.
		/// \return An iterator to the first element of the list.
		Iterator begin();

		/// Gets a constant iterator to the first element of the list.
		/// \return A constant iterator to the first element of the list.
		ConstIterator begin() const;

		/// Gets an iterator to the past the last element of the list.
		/// \return An iterator to the past the last element of the list.
		Iterator end();

		/// Gets a constant iterator to the past the last element of the list.
		/// \return A constant iterator to the past the last element of the
		/// list.
		ConstIterator end() const;

		/// Inserts an element into the list, before the given position.
		/// \param pos The position where to put \a value.
		/// \param value The value to add.
		/// \return An iterator to the inserted element.
		Iterator insert(Iterator pos, const T& value);

		/// Inserts an element into the list, before the given position.
		/// \param pos The position where to put \a value.
		/// \param value The value to add.
		/// \return An iterator to the inserted element.
		Iterator insert(Iterator pos, T&& value);

		/// Erases an element of the list.
		/// \param pos An iterator to the element to erase.
		/// \return An iterator to the element following the erased element.
		Iterator erase(Iterator pos);

		/// Erases a sequence of elements from the list.
		/// \param first The first element to erase.
		/// \param last The element following the last element to erase.
		/// \return An iterator to the element following the last erased
		/// element.
		Iterator erase(Iterator first, Iterator last);

	private:
		Iterator insertImpl(Iterator pos);

		/// The first node of the list.
		NodeType* _begin;

		/// The last node of the list.
		NodeType* _end;

		/// The number of elements in the list.
		size_t _size;

		/// The used allocator for allocating nodes.
		Allocator<NodeType>& _allocator;
};

template <class T>
List<T>::List(Allocator<NodeType>& allocator):
	_size{0UL},
	_allocator{allocator}
{
	_begin = _end = _allocator.construct();
}

template <class T>
List<T>::List(const List<T>& other):
	List(other._allocator)
{
	for(auto& value : other)
		pushBack(value);
}

template <class T>
List<T>::List(List<T>&& other):
	List(other._allocator)
{
	swap(_begin, other._begin);
	swap(_end, other._end);
	swap(_size, other._size);
}

template <class T>
List<T>::~List()
{
	clear();
	_allocator.deallocate(_end);
}

template <class T>
List<T>& List<T>::operator=(List<T> other)
{
	swap(*this, other);
}

template <class T>
bool List<T>::empty() const
{
	return size() == 0;
}

template <class T>
size_t List<T>::size() const
{
	return _size;
}

template <class T>
T& List<T>::back()
{
	return _end->previous->_value;
}

template <class T>
const T& List<T>::back() const
{
	return _end->previous->_value;
}

template <class T>
T& List<T>::front()
{
	return _begin->value;
}

template <class T>
const T& List<T>::front() const
{
	return _begin->value;
}

template <class T>
void List<T>::clear()
{
	erase(begin(), end());
}

template <class T>
void List<T>::pushBack(const T& value)
{
	insert(end(), value);
}

template <class T>
void List<T>::pushBack(T&& value)
{
	insert(end(), forward<T>(value));
}

template <class T>
void List<T>::pushFront(const T& value)
{
	insert(begin(), value);
}

template <class T>
void List<T>::pushFront(T&& value)
{
	insert(begin(), forward<T>(value));
}

template <class T>
T List<T>::popBack()
{
	const T lastValue{back()};
	erase(--end());
	return lastValue;
}

template <class T>
T List<T>::popFront()
{
	const T firstValue{front()};
	erase(begin());
	return firstValue;
}

template <class T>
typename List<T>::Iterator List<T>::begin()
{
	return Iterator(_begin);
}

template <class T>
typename List<T>::ConstIterator List<T>::begin() const
{
	return ConstIterator(_begin);
}

template <class T>
typename List<T>::Iterator List<T>::end()
{
	return Iterator(_end);
}

template <class T>
typename List<T>::ConstIterator List<T>::end() const
{
	return ConstIterator(_end);
}

template <class T>
typename List<T>::Iterator List<T>::insert(Iterator pos, const T& value)
{
	auto it(insertImpl(pos));
	*it = value;
	return it;
}

template <class T>
typename List<T>::Iterator List<T>::insert(Iterator pos, T&& value)
{
	auto it(insertImpl(pos));
	*it = forward<T>(value);
	return it;
}

template <class T>
typename List<T>::Iterator List<T>::erase(Iterator pos)
{
	Iterator tmp{pos};
	++tmp;
	return erase(pos, tmp);
}

template <class T>
typename List<T>::Iterator List<T>::erase(Iterator first, Iterator last)
{
	if(first._node == _begin)
		_begin = last._node;
	else if(first != last)
		first._node->previous->next = last._node;
	if(last._node == _end)
		_end->previous = first._node->previous;
	else if(first != last)
		last._node->previous = first._node->previous;
	while(first != last)
	{
		_allocator.destroy(first._node);
		++first;
		--_size;
	}
	return last;
}

template <class T>
typename List<T>::Iterator List<T>::insertImpl(Iterator pos)
{
	NodeType* node{_allocator.construct()};
	node->previous = pos._node->previous;
	node->next = pos._node;
	pos._node->previous = node;
	if(node->previous == nullptr)
		_begin = node;
	else
		node->previous->next = node;
	++_size;
	return Iterator(node);
}

#endif // LIST_HPP
