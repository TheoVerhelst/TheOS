#ifndef NODE_HPP
#define NODE_HPP

// Forward declarations
template <typename T>
class List;

namespace impl
{

/// Represents a node in the list.
/// \tparam T The type of element to store as value of the node.
template <class T>
struct ListNode
{
	T value;                    ///< The value of the node.
	ListNode* next{nullptr};    ///< The next node.
	ListNode* previous{nullptr};///< The previous node.
};

template <typename T, typename NodeType>
class NodeIterator
{
	public:
		/// Constructor from list node.
		/// \param node The node that the iterator has to point to.
		explicit NodeIterator(NodeType* node);

		/// Dereferencement operator.
		/// \return A reference to the pointed object.
		T& operator*() const;

		/// Dereferencement operator.
		/// \return A pointer to the pointed object.
		T* operator->() const;

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
		friend List<T>;
		NodeType* _node; ///< The underlying node.
};

} // namespace impl

namespace impl
{

template <typename T, typename NodeType>
NodeIterator<T, NodeType>::NodeIterator(NodeType* node):
	_node{node}
{
}


template <typename T, typename NodeType>
T&  NodeIterator<T, NodeType>::operator*() const
{
	return _node->value;
}


template <typename T, typename NodeType>
T*  NodeIterator<T, NodeType>::operator->() const
{
	return &_node->value;
}


template <typename T, typename NodeType>
NodeIterator<T, NodeType>& NodeIterator<T, NodeType>::operator++()
{
	_node = _node->next;
	return static_cast<NodeIterator&>(*this);
}


template <typename T, typename NodeType>
NodeIterator<T, NodeType> NodeIterator<T, NodeType>::operator++(int)
{
	NodeIterator tmp{*this};
	_node = _node->next;
	return tmp;
}


template <typename T, typename NodeType>
NodeIterator<T, NodeType>& NodeIterator<T, NodeType>::operator--()
{
	_node = _node->previous;
	return static_cast<NodeIterator&>(*this);
}


template <typename T, typename NodeType>
NodeIterator<T, NodeType> NodeIterator<T, NodeType>::operator--(int)
{
	NodeIterator tmp{*this};
	_node = _node->previous;
	return tmp;
}


template <typename T, typename NodeType>
bool NodeIterator<T, NodeType>::operator==(const NodeIterator<T, NodeType>& other) const
{
	return _node == other._node;
}


template <typename T, typename NodeType>
bool NodeIterator<T, NodeType>::operator!=(const NodeIterator<T, NodeType>& other) const
{
	return _node != other._node;
}

} // namespace impl

#endif // NODE_HPP
