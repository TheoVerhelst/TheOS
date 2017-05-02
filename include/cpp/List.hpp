#ifndef LIST_HPP
#define LIST_HPP

#include <std/cstddef>
#include <std/type_traits>
#include <cpp/utility.hpp>
#include <cpp/memory.hpp>

/// \addtogroup Cpp
/// \{

namespace details
{

/// Represents a node in the list.
/// \tparam U The type of element to store as value of the node.
template <class T>
struct ListNode
{
	T _value;                    ///< The value of the node.
	ListNode* _next{nullptr};    ///< The next node.
	ListNode* _previous{nullptr};///< The previous node.
};

} // namespace details

/// Dynamic double-linked list. This class has approximatively the same
/// interface as `std::list`, and is part of the pseudo-implementation of the
/// standard C++ library.
///
/// This class can be used with a custom allocator, which is useful when the
/// memory have to be used in a certain manner (e.g. when the operator new is
/// not yet available).
/// \tparam T The type of element.
/// \tparam AllocatorType The type of allocator to use.
template <class T, class AllocatorType = Allocator<details::ListNode<T>>>
class List
{
	static_assert(std::is_same<typename AllocatorType::ValueType, details::ListNode<T>>::value,
			"AllocatorType must allocate details::ListNode<T> objects.");
	private:
		template <typename U, typename NodeType>
		class NodeIterator
		{
			public:
				/// Constructor from list node.
				/// \param node The node that the iterator has to point to.
				explicit NodeIterator(NodeType* node) noexcept;

				/// Dereferencement operator.
				/// \return A reference to the pointed object.
				U& operator*() const noexcept;

				/// Dereferencement operator.
				/// \return A pointer to the pointed object.
				U* operator->() const noexcept;

				/// Increment operator. This advances the iterator by one
				/// element.
				/// \return A reference to the advanced iterator.
				NodeIterator& operator++() noexcept;

				/// Increment operator. This advances the iterator by one
				/// element.
				/// \return A reference to the old, non advanced iterator.
				NodeIterator operator++(int) noexcept;

				/// Decrement operator. This moves the iterator by one
				/// element back.
				/// \return A reference to the moved iterator.
				NodeIterator& operator--() noexcept;

				/// Decrement operator. This moves the iterator by one
				/// element back.
				/// \return A reference to the old, non advanced iterator.
				NodeIterator operator--(int) noexcept;

				/// Comparison operator.
				/// \param other The other iterator to compare to.
				/// \return True if the iterators point to the same node, false
				/// otherwhise.
				bool operator==(const NodeIterator& other) const noexcept;

				/// Comparison operator.
				/// \param other The other iterator to compare to.
				/// \return True if the iterators do not point to the same node,
				/// false otherwhise.
				bool operator!=(const NodeIterator& other) const noexcept;

			private:
				NodeType* _node; ///< The underlying node.
				friend class List;
		};

	public:
		typedef NodeIterator<T, details::ListNode<T>> iterator;          ///< Non constant iterator.
		typedef NodeIterator<const T, const details::ListNode<T>> constIterator;///< Constant iterator.

		/// Default constructor.
		/// \param allocator The allocator to use.
		List(const AllocatorType& allocator = AllocatorType());

		/// Copy constructor.
		/// \param other The other list to copy.
		List(const List& other);// TODO copy constructor does not work

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
		void popBack();

		/// Removes the last element of the list.
		/// \pre not empty().
		void popFront();

		/// Gets an iterator to the first element of the list.
		/// \return An iterator to the first element of the list.
		iterator begin();

		/// Gets a constant iterator to the first element of the list.
		/// \return A constant iterator to the first element of the list.
		constIterator begin() const;

		/// Gets an iterator to the past the last element of the list.
		/// \return An iterator to the past the last element of the list.
		iterator end();

		/// Gets a constant iterator to the past the last element of the list.
		/// \return A constant iterator to the past the last element of the
		/// list.
		constIterator end() const;

		/// Inserts an element into the list, before the given position.
		/// \param pos The position where to put \a value.
		/// \param value The value to add.
		/// \return An iterator to the inserted element.
		iterator insert(iterator pos, const T& value);

		/// Inserts an element into the list, before the given position.
		/// \param pos The position where to put \a value.
		/// \param value The value to add.
		/// \return An iterator to the inserted element.
		iterator insert(iterator pos, T&& value);

		/// Inserts an element into the list, before the given position.
		/// \param pos The position where to put \a value.
		/// \param value The value to add.
		/// \return An iterator to the inserted element.
		iterator insert(constIterator pos, const T& value);

		/// Inserts an element into the list, before the given position.
		/// \param pos The position where to put \a value.
		/// \param value The value to add.
		/// \return An iterator to the inserted element.
		iterator insert(constIterator pos, T&& value);

		/// Erases an element of the list.
		/// \param pos An iterator to the element to erase.
		/// \return An iterator to the element following the erased element.
		iterator erase(iterator pos);

		/// Erases an element of the list.
		/// \param pos An iterator to the element to erase.
		/// \return An iterator to the element following the erased element.
		iterator erase(constIterator pos);

		/// Erases a sequence of elements from the list.
		/// \param first The first element to erase.
		/// \param last The element following the last element to erase.
		/// \return An iterator to the element following the last erased
		/// element.
		iterator erase(iterator first, iterator last);

		/// Erases a sequence of elements from the list.
		/// \param first The first element to erase.
		/// \param last The element following the last element to erase.
		/// \return An iterator to the element following the last erased
		/// element.
		iterator erase(constIterator first, constIterator last);

	private:
		/// The first node of the list.
		details::ListNode<T>* _begin;

		/// The last node of the list.
		details::ListNode<T>* _end;

		/// The number of elements in the list.
		size_t _size;

		/// The used allocator for allocating nodes.
		AllocatorType _allocator;
};

/// \}

// List
template <class T, class AllocatorType>
List<T, AllocatorType>::List(const AllocatorType& allocator):
	_size{0UL},
	_allocator{allocator}
{
	_begin = _end = _allocator.construct();
}

template <class T, class AllocatorType>
List<T, AllocatorType>::List(const List<T, AllocatorType>& other):
	List()
{
	for(auto& value : other)
		pushBack(value);
}

template <class T, class AllocatorType>
List<T, AllocatorType>::List(List<T, AllocatorType>&& other):
	List()
{
	swap(_begin, other._begin);
	swap(_end, other._end);
	swap(_size, other._size);
}

template <class T, class AllocatorType>
List<T, AllocatorType>::~List()
{
	clear();
	_allocator.deallocate(_end);
}

template <class T, class AllocatorType>
List<T, AllocatorType>& List<T, AllocatorType>::operator=(List<T, AllocatorType> other)
{
	swap(*this, other);
}

template <class T, class AllocatorType>
bool List<T, AllocatorType>::empty() const
{
	return _begin == _end;
}

template <class T, class AllocatorType>
size_t List<T, AllocatorType>::size() const
{
	return _size;
}

template <class T, class AllocatorType>
T& List<T, AllocatorType>::back()
{
	return _end->_previous->_value;
}

template <class T, class AllocatorType>
const T& List<T, AllocatorType>::back() const
{
	return _end->_previous->_value;
}

template <class T, class AllocatorType>
T& List<T, AllocatorType>::front()
{
	return _begin->_value;
}

template <class T, class AllocatorType>
const T& List<T, AllocatorType>::front() const
{
	return _begin->_value;
}

template <class T, class AllocatorType>
void List<T, AllocatorType>::clear()
{
	erase(begin(), end());
}

template <class T, class AllocatorType>
void List<T, AllocatorType>::pushBack(const T& value)
{
	insert(end(), value);
}

#include <iostream>

template <class T, class AllocatorType>
void List<T, AllocatorType>::pushBack(T&& value)
{
	insert(end(), forward<T>(value));
}

template <class T, class AllocatorType>
void List<T, AllocatorType>::pushFront(const T& value)
{
	insert(begin(), value);
}

template <class T, class AllocatorType>
void List<T, AllocatorType>::pushFront(T&& value)
{
	insert(begin(), forward<T>(value));
}

template <class T, class AllocatorType>
void List<T, AllocatorType>::popBack()
{
	iterator tmp{end()};
	erase(--tmp);
}

template <class T, class AllocatorType>
void List<T, AllocatorType>::popFront()
{
	erase(begin());
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::begin()
{
	return iterator(_begin);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::constIterator List<T, AllocatorType>::begin() const
{
	return constIterator(_begin);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::end()
{
	return iterator(_end);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::constIterator List<T, AllocatorType>::end() const
{
	return constIterator(_end);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(iterator pos, const T& value)
{
	details::ListNode<T>* node{_allocator.construct()};
	node->_value = value;
	node->_previous = pos._node->_previous;
	node->_next = pos._node;
	pos._node->_previous = node;
	if(node->_previous == nullptr)
		_begin = node;
	else
		node->_previous->_next = node;
	++_size;
	return iterator(node);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(iterator pos, T&& value)
{
	details::ListNode<T>* node{_allocator.construct()};
	node->_value = forward<T>(value);
	node->_previous = pos._node->_previous;
	node->_next = pos._node;
	pos._node->_previous = node;
	if(node->_previous == nullptr)
		_begin = node;
	else
		node->_previous->_next = node;
	++_size;
	return iterator(node);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(constIterator pos, const T& value)
{
	return insert(iterator(const_cast<details::ListNode<T>*>(pos._node)), value);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(constIterator pos, T&& value)
{
	return insert(iterator(const_cast<details::ListNode<T>*>(pos._node)), forward<T>(value));
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::erase(iterator pos)
{
	iterator tmp{pos};
	++tmp;
	return erase(pos, tmp);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::erase(constIterator pos)
{
	return erase(iterator(const_cast<details::ListNode<T>*>(pos._node)));
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::erase(iterator first, iterator last)
{
	if(first._node == _begin)
		_begin = last._node;
	else if(first != last)
		first._node->_previous->_next = last._node;
	if(last._node == _end)
		_end->_previous = first._node->_previous;
	else if(first != last)
		last._node->_previous = first._node->_previous;
	while(first != last)
	{
		_allocator.destroy(first._node);
		++first;
		--_size;
	}
	return last;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::erase(constIterator first, constIterator last)
{
	return erase(iterator(const_cast<details::ListNode<T>*>(first._node)), iterator(const_cast<details::ListNode<T>*>(last._node)));
}

// NodeIterator

template <class T, class AllocatorType>
template <typename U, typename NodeType>
List<T, AllocatorType>::NodeIterator<U, NodeType>::NodeIterator(NodeType* node) noexcept:
	_node{node}
{
}

template <class T, class AllocatorType>
template <typename U, typename NodeType>
U&  List<T, AllocatorType>::NodeIterator<U, NodeType>::operator*() const noexcept
{
	return _node->_value;
}

template <class T, class AllocatorType>
template <typename U, typename NodeType>
U*  List<T, AllocatorType>::NodeIterator<U, NodeType>::operator->() const noexcept
{
	return &_node->_value;
}

template <class T, class AllocatorType>
template <typename U, typename NodeType>
List<T, AllocatorType>::NodeIterator<U, NodeType>& List<T, AllocatorType>::NodeIterator<U, NodeType>::operator++() noexcept
{
	_node = _node->_next;
	return static_cast<NodeIterator&>(*this);
}

template <class T, class AllocatorType>
template <typename U, typename NodeType>
List<T, AllocatorType>::NodeIterator<U, NodeType> List<T, AllocatorType>::NodeIterator<U, NodeType>::operator++(int) noexcept
{
	NodeIterator tmp{*this};
	_node = _node->_next;
	return tmp;
}

template <class T, class AllocatorType>
template <typename U, typename NodeType>
List<T, AllocatorType>::NodeIterator<U, NodeType>& List<T, AllocatorType>::NodeIterator<U, NodeType>::operator--() noexcept
{
	_node = _node->_previous;
	return static_cast<NodeIterator&>(*this);
}

template <class T, class AllocatorType>
template <typename U, typename NodeType>
List<T, AllocatorType>::NodeIterator<U, NodeType> List<T, AllocatorType>::NodeIterator<U, NodeType>::operator--(int) noexcept
{
	NodeIterator tmp{*this};
	_node = _node->_previous;
	return tmp;
}

template <class T, class AllocatorType>
template <typename U, typename NodeType>
bool List<T, AllocatorType>::NodeIterator<U, NodeType>::operator==(const NodeIterator<U, NodeType>& other) const noexcept
{
	return _node == other._node;
}

template <class T, class AllocatorType>
template <typename U, typename NodeType>
bool List<T, AllocatorType>::NodeIterator<U, NodeType>::operator!=(const NodeIterator<U, NodeType>& other) const noexcept
{
	return _node != other._node;
}

#endif// LIST_HPP
