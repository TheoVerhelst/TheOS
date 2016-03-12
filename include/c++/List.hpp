#ifndef LIST_HPP
#define LIST_HPP

#include <utility>
#include <cstddef>
#include <type_traits>
#include <memory.hpp>

/// Classes used in the implementation of the class List.
namespace details
{

/// Represents a node in the list.
/// \tparam T The type of element to store as value of the node.
template <class T>
struct ListNode
{
	T _value;                     ///< The value of the node.
	ListNode* _next = nullptr;    ///< The next node.
	ListNode* _previous = nullptr;///< The previous node.
};

}// namespace details

template <class T, class AllocatorType = Allocator<details::ListNode<T>>>
class List
{
	static_assert(std::is_same<typename AllocatorType::ValueType, details::ListNode<T>>::value,
			"AllocatorType must allocate details::ListNode<T> objects.");
	private:
		//TODO template <class U>; typedef NodeIterator<T> iterator; typedef NodeIterator<const T> constIterator;
		class NodeIterator
		{
			public:
				NodeIterator() = default;
				NodeIterator(const NodeIterator& other) = default;
				explicit NodeIterator(details::ListNode<T>* node) noexcept;
				T& operator*() const noexcept;
				T* operator->() const noexcept;
				NodeIterator& operator++() noexcept;
				NodeIterator operator++(int) noexcept;
				NodeIterator& operator--() noexcept;
				NodeIterator operator--(int) noexcept;
				bool operator==(const NodeIterator& other) const noexcept;
				bool operator!=(const NodeIterator& other) const noexcept;

			private:
				details::ListNode<T>* _node;
				friend class List;
		};

		class NodeConstIterator
		{
			public:
				NodeConstIterator() = default;
				NodeConstIterator(const NodeConstIterator& other) = default;
				explicit NodeConstIterator(const details::ListNode<T>* node) noexcept;
				const T& operator*() const noexcept;
				const T* operator->() const noexcept;
				NodeConstIterator& operator++() noexcept;
				NodeConstIterator operator++(int) noexcept;
				NodeConstIterator& operator--() noexcept;
				NodeConstIterator operator--(int) noexcept;
				bool operator==(const NodeConstIterator& other) const noexcept;
				bool operator!=(const NodeConstIterator& other) const noexcept;

			private:
				const details::ListNode<T>* _node;
				friend class List;
		};

	public:
		typedef NodeIterator iterator;
		typedef NodeConstIterator constIterator;

		List(const AllocatorType& allocator = AllocatorType());
		List(const List& other);// TODO copy constructor does not work
		List(List&& other);
		~List();
		List& operator=(List other);
		AllocatorType getAllocator() const;
		bool empty() const;
		size_t size() const;
		T& back();             ///< \pre not empty().
		const T& back() const; ///< \pre not empty().
		T& front();            ///< \pre not empty().
		const T& front() const;///< \pre not empty().
		void clear();
		void pushBack(const T& value);
		void pushBack(T&& value);
		void pushFront(const T& value);
		void pushFront(T&& value);
		void popBack();
		void popFront();
		iterator begin();
		constIterator cbegin() const;
		iterator end();
		constIterator cend() const;
		iterator insert(iterator pos, const T& value);
		iterator insert(iterator pos, T&& value);
		iterator insert(constIterator pos, const T& value);
		iterator insert(constIterator pos, T&& value);
		iterator erase(iterator pos);
		iterator erase(constIterator pos);
		iterator erase(iterator first, iterator last);
		iterator erase(constIterator first, constIterator last);

	private:
		details::ListNode<T>* _begin;
		details::ListNode<T>* _end;
		size_t _size;
		AllocatorType _allocator;
};

// List
template <class T, class AllocatorType>
List<T, AllocatorType>::List(const AllocatorType& allocator):
	_size{0UL},
	_allocator{allocator}
{
	_begin = _end = _allocator.allocate();
}

template <class T, class AllocatorType>
List<T, AllocatorType>::List(const List<T, AllocatorType>& other):
	List()
{
	details::ListNode<T>* previousNode{_begin};
	details::ListNode<T>* nextNode;
	for(const details::ListNode<T>* node{other._begin}; node != other._end; node = node->_next)
	{
		previousNode->_value = node->_value;
		nextNode = _allocator.allocate();
		nextNode->_previous = previousNode;
		previousNode->_next = nextNode;
		++_size;
	}
	_end = nextNode;
}

template <class T, class AllocatorType>
List<T, AllocatorType>::List(List<T, AllocatorType>&& other):
	List()
{
	std::swap(_begin, other._begin);
	std::swap(_end, other._end);
	std::swap(_size, other._size);
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
	std::swap(*this, other);
}

template <class T, class AllocatorType>
AllocatorType List<T, AllocatorType>::getAllocator() const
{
	return _allocator;
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

template <class T, class AllocatorType>
void List<T, AllocatorType>::pushBack(T&& value)
{
	insert(end(), std::forward<T>(value));
}

template <class T, class AllocatorType>
void List<T, AllocatorType>::pushFront(const T& value)
{
	insert(begin(), value);
}

template <class T, class AllocatorType>
void List<T, AllocatorType>::pushFront(T&& value)
{
	insert(begin(), std::forward<T>(value));
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
typename List<T, AllocatorType>::constIterator List<T, AllocatorType>::cbegin() const
{
	return constIterator(_begin);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::end()
{
	return iterator(_end);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::constIterator List<T, AllocatorType>::cend() const
{
	return constIterator(_end);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(iterator pos, const T& value)
{
	details::ListNode<T>* node{_allocator.allocate()};
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
	details::ListNode<T>* node{_allocator.allocate()};
	node->_value = std::forward<T>(value);
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
	return insert(iterator(const_cast<details::ListNode<T>*>(pos._node)), std::forward<T>(value));
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
		_allocator.deallocate(first._node);
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
List<T, AllocatorType>::NodeIterator::NodeIterator(details::ListNode<T>* node) noexcept:
	_node(node)
{
}

template <class T, class AllocatorType>
T&  List<T, AllocatorType>::NodeIterator::operator*() const noexcept
{
	return _node->_value;
}

template <class T, class AllocatorType>
T*  List<T, AllocatorType>::NodeIterator::operator->() const noexcept
{
	return &_node->_value;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeIterator& List<T, AllocatorType>::NodeIterator::operator++() noexcept
{
	_node = _node->_next;
	return *this;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeIterator List<T, AllocatorType>::NodeIterator::operator++(int) noexcept
{
	NodeIterator tmp{*this};
	_node = _node->_next;
	return tmp;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeIterator& List<T, AllocatorType>::NodeIterator::operator--() noexcept
{
	_node = _node->_previous;
	return *this;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeIterator List<T, AllocatorType>::NodeIterator::operator--(int) noexcept
{
	NodeIterator tmp{*this};
	_node = _node->_previous;
	return tmp;
}

template <class T, class AllocatorType>
bool List<T, AllocatorType>::NodeIterator::operator==(const List<T, AllocatorType>::NodeIterator& other) const noexcept
{
	return _node == other._node;
}

template <class T, class AllocatorType>
bool List<T, AllocatorType>::NodeIterator::operator!=(const List<T, AllocatorType>::NodeIterator& other) const noexcept
{
	return _node != other._node;
}

// NodeConstIterator

template <class T, class AllocatorType>
List<T, AllocatorType>::NodeConstIterator::NodeConstIterator(const details::ListNode<T>* node) noexcept:
	_node(node)
{
}

template <class T, class AllocatorType>
const T&  List<T, AllocatorType>::NodeConstIterator::operator*() const noexcept
{
	return _node->_value;
}

template <class T, class AllocatorType>
const T*  List<T, AllocatorType>::NodeConstIterator::operator->() const noexcept
{
	return &_node->_value;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeConstIterator& List<T, AllocatorType>::NodeConstIterator::operator++() noexcept
{
	_node = _node->_next;
	return *this;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeConstIterator List<T, AllocatorType>::NodeConstIterator::operator++(int) noexcept
{
	NodeConstIterator tmp{*this};
	_node = _node->_next;
	return tmp;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeConstIterator& List<T, AllocatorType>::NodeConstIterator::operator--() noexcept
{
	_node = _node->_previous;
	return *this;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeConstIterator List<T, AllocatorType>::NodeConstIterator::operator--(int) noexcept
{
	NodeConstIterator tmp{*this};
	_node = _node->_previous;
	return tmp;
}

template <class T, class AllocatorType>
bool List<T, AllocatorType>::NodeConstIterator::operator==(const List<T, AllocatorType>::NodeConstIterator& other) const noexcept
{
	return _node == other._node;
}

template <class T, class AllocatorType>
bool List<T, AllocatorType>::NodeConstIterator::operator!=(const List<T, AllocatorType>::NodeConstIterator& other) const noexcept
{
	return _node != other._node;
}


#endif// LIST_HPP
