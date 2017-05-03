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
/// \tparam Allocator<T> The type of allocator to use.
template <class T>
class List
{
	private:
		template <typename U, typename NodeType>
		class NodeIterator
		{
			public:
				/// Default constructor, constructs an invalid iterator.
				NodeIterator() = default;

				/// Constructor from list node.
				/// \param node The node that the iterator has to point to.
				explicit NodeIterator(NodeType* node);

				/// Dereferencement operator.
				/// \return A reference to the pointed object.
				U& operator*() const;

				/// Dereferencement operator.
				/// \return A pointer to the pointed object.
				U* operator->() const;

				/// Increment operator. This advances the iterator by one
				/// element.
				/// \return A reference to the advanced iterator.
				NodeIterator& operator++();

				/// Increment operator. This advances the iterator by one
				/// element.
				/// \return A reference to the old, non advanced iterator.
				NodeIterator operator++(int);

				/// Decrement operator. This moves the iterator by one
				/// element back.
				/// \return A reference to the moved iterator.
				NodeIterator& operator--();

				/// Decrement operator. This moves the iterator by one
				/// element back.
				/// \return A reference to the old, non advanced iterator.
				NodeIterator operator--(int);

				/// Comparison operator.
				/// \param other The other iterator to compare to.
				/// \return True if the iterators point to the same node, false
				/// otherwhise.
				bool operator==(const NodeIterator& other) const;

				/// Comparison operator.
				/// \param other The other iterator to compare to.
				/// \return True if the iterators do not point to the same node,
				/// false otherwhise.
				bool operator!=(const NodeIterator& other) const;

			private:
				NodeType* _node = nullptr; ///< The underlying node.
				friend class List;
		};

	public:
		typedef details::ListNode<T> NodeType;
		typedef NodeIterator<T, NodeType> iterator;                 ///< Non constant iterator.
		typedef NodeIterator<const T, const NodeType> constIterator;///< Constant iterator.

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

		/// Erases an element of the list.
		/// \param pos An iterator to the element to erase.
		/// \return An iterator to the element following the erased element.
		iterator erase(iterator pos);

		/// Erases a sequence of elements from the list.
		/// \param first The first element to erase.
		/// \param last The element following the last element to erase.
		/// \return An iterator to the element following the last erased
		/// element.
		iterator erase(iterator first, iterator last);

	private:
		iterator insertImpl(iterator pos);

		/// The first node of the list.
		NodeType* _begin;

		/// The last node of the list.
		NodeType* _end;

		/// The number of elements in the list.
		size_t _size;

		/// The used allocator for allocating nodes.
		Allocator<NodeType>& _allocator;
};

/// \}

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
	return _begin == _end;
}

template <class T>
size_t List<T>::size() const
{
	return _size;
}

template <class T>
T& List<T>::back()
{
	return _end->_previous->_value;
}

template <class T>
const T& List<T>::back() const
{
	return _end->_previous->_value;
}

template <class T>
T& List<T>::front()
{
	return _begin->_value;
}

template <class T>
const T& List<T>::front() const
{
	return _begin->_value;
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
void List<T>::popBack()
{
	erase(--end());
}

template <class T>
void List<T>::popFront()
{
	erase(begin());
}

template <class T>
typename List<T>::iterator List<T>::begin()
{
	return iterator(_begin);
}

template <class T>
typename List<T>::constIterator List<T>::begin() const
{
	return constIterator(_begin);
}

template <class T>
typename List<T>::iterator List<T>::end()
{
	return iterator(_end);
}

template <class T>
typename List<T>::constIterator List<T>::end() const
{
	return constIterator(_end);
}

template <class T>
typename List<T>::iterator List<T>::insert(iterator pos, const T& value)
{
	auto it(insertImpl(pos));
	*it = value;
	return it;
}

template <class T>
typename List<T>::iterator List<T>::insert(iterator pos, T&& value)
{
	auto it(insertImpl(pos));
	*it = forward<T>(value);
	return it;
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator pos)
{
	iterator tmp{pos};
	++tmp;
	return erase(pos, tmp);
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator first, iterator last)
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

template <class T>
typename List<T>::iterator List<T>::insertImpl(iterator pos)
{
	NodeType* node{_allocator.construct()};
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

// NodeIterator

template <class T>
template <typename U, typename NodeType>
List<T>::NodeIterator<U, NodeType>::NodeIterator(NodeType* node) noexcept:
	_node{node}
{
}

template <class T>
template <typename U, typename NodeType>
U&  List<T>::NodeIterator<U, NodeType>::operator*() const noexcept
{
	return _node->_value;
}

template <class T>
template <typename U, typename NodeType>
U*  List<T>::NodeIterator<U, NodeType>::operator->() const noexcept
{
	return &_node->_value;
}

template <class T>
template <typename U, typename NodeType>
List<T>::NodeIterator<U, NodeType>& List<T>::NodeIterator<U, NodeType>::operator++() noexcept
{
	_node = _node->_next;
	return static_cast<NodeIterator&>(*this);
}

template <class T>
template <typename U, typename NodeType>
List<T>::NodeIterator<U, NodeType> List<T>::NodeIterator<U, NodeType>::operator++(int) noexcept
{
	NodeIterator tmp{*this};
	_node = _node->_next;
	return tmp;
}

template <class T>
template <typename U, typename NodeType>
List<T>::NodeIterator<U, NodeType>& List<T>::NodeIterator<U, NodeType>::operator--() noexcept
{
	_node = _node->_previous;
	return static_cast<NodeIterator&>(*this);
}

template <class T>
template <typename U, typename NodeType>
List<T>::NodeIterator<U, NodeType> List<T>::NodeIterator<U, NodeType>::operator--(int) noexcept
{
	NodeIterator tmp{*this};
	_node = _node->_previous;
	return tmp;
}

template <class T>
template <typename U, typename NodeType>
bool List<T>::NodeIterator<U, NodeType>::operator==(const NodeIterator<U, NodeType>& other) const noexcept
{
	return _node == other._node;
}

template <class T>
template <typename U, typename NodeType>
bool List<T>::NodeIterator<U, NodeType>::operator!=(const NodeIterator<U, NodeType>& other) const noexcept
{
	return _node != other._node;
}

#endif// LIST_HPP
