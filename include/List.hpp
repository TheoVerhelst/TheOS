#ifndef LIST_HPP
#define LIST_HPP

#include <utility>

//Forward declarations
template <typename T>
class Allocator;

namespace details
{

template <class T>
struct ListNode
{
	T value;
	ListNode* next = nullptr;
	ListNode* previous = nullptr;
};

}// namespace details

template <class T, class AllocatorType = Allocator<details::ListNode<T>>>
class List
{
	static_assert(sizeof(typename AllocatorType::valueType) == sizeof(details::ListNode<T>),
			"AllocatorType cannot be used because it allocates the wrong size");
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
		AllocatorType getAllocator() const;
		bool empty() const;
		size_t size() const;

		/// \pre not empty().
		T& back();

		/// \pre not empty().
		const T& back() const;

		/// \pre not empty().
		T& front();

		/// \pre not empty().
		const T& front() const;
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
	return _end->previous->value;
}

template <class T, class AllocatorType>
const T& List<T, AllocatorType>::back() const
{
	return _end->previous->value;
}

template <class T, class AllocatorType>
T& List<T, AllocatorType>::front()
{
	return _begin->value;
}

template <class T, class AllocatorType>
const T& List<T, AllocatorType>::front() const
{
	return _begin->value;
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
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(List<T, AllocatorType>::iterator pos, const T& value)
{
	//TODO be sure that this will always be possible, even if T has not move assignment operator
	return insert(pos, T(value));
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(List<T, AllocatorType>::iterator pos, T&& value)
{
	details::ListNode<T>* node{_allocator.allocate()};
	node->value = std::forward<T>(value);
	node->previous = pos._node->previous;
	node->next = pos._node;
	pos._node->previous = node;
	if(node->previous == nullptr)
		_begin = node;
	++_size;
	return iterator(node);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(List<T, AllocatorType>::constIterator pos, const T& value)
{
	return insert(iterator(const_cast<details::ListNode<T>*>(pos._node)), value);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::insert(List<T, AllocatorType>::constIterator pos, T&& value)
{
	return insert(iterator(const_cast<details::ListNode<T>*>(pos._node)), std::forward<T>(value));
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::erase(List<T, AllocatorType>::iterator pos)
{
	iterator tmp{pos};
	++tmp;
	return erase(pos, tmp);
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::erase(List<T, AllocatorType>::constIterator pos)
{
	return erase(iterator(const_cast<details::ListNode<T>*>(pos._node)));
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::erase(List<T, AllocatorType>::iterator first, List<T, AllocatorType>::iterator last)
{
	if(first._node == _begin)
		_begin = last._node;
	else if(first != last)
		first._node->previous->next = last._node;
	if(last._node == _end)
		_end->previous = first._node->previous;
	else if(first != last)
		last._node->next->previous = first._node->previous;
	while(first != last)
	{
		_allocator.deallocate(first._node);
		++first;
		--_size;
	}
	return last;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::iterator List<T, AllocatorType>::erase(List<T, AllocatorType>::constIterator first, List<T, AllocatorType>::constIterator last)
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
	return _node->value;
}

template <class T, class AllocatorType>
T*  List<T, AllocatorType>::NodeIterator::operator->() const noexcept
{
	return &_node->value;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeIterator& List<T, AllocatorType>::NodeIterator::operator++() noexcept
{
	_node = _node->next;
	return *this;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeIterator List<T, AllocatorType>::NodeIterator::operator++(int) noexcept
{
	NodeIterator tmp{*this};
	_node = _node->next;
	return tmp;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeIterator& List<T, AllocatorType>::NodeIterator::operator--() noexcept
{
	_node = _node->previous;
	return *this;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeIterator List<T, AllocatorType>::NodeIterator::operator--(int) noexcept
{
	NodeIterator tmp{*this};
	_node = _node->previous;
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
	return _node->value;
}

template <class T, class AllocatorType>
const T*  List<T, AllocatorType>::NodeConstIterator::operator->() const noexcept
{
	return &_node->value;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeConstIterator& List<T, AllocatorType>::NodeConstIterator::operator++() noexcept
{
	_node = _node->next;
	return *this;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeConstIterator List<T, AllocatorType>::NodeConstIterator::operator++(int) noexcept
{
	NodeConstIterator tmp{*this};
	_node = _node->next;
	return tmp;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeConstIterator& List<T, AllocatorType>::NodeConstIterator::operator--() noexcept
{
	_node = _node->previous;
	return *this;
}

template <class T, class AllocatorType>
typename List<T, AllocatorType>::NodeConstIterator List<T, AllocatorType>::NodeConstIterator::operator--(int) noexcept
{
	NodeConstIterator tmp{*this};
	_node = _node->previous;
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
