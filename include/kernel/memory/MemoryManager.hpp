#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <cstddef>
#include <type_traits>
#include <kernel/memory/Byte.hpp>
#include <memory.hpp>
#include <math.hpp>
#include <List.hpp>
#include <Printer.hpp>
#include <Array.hpp>

/// Holds some things related to the implementation of the memory management.
/// The memory is implemented with the buddy algorithm.
template <class AllocatorType = Allocator<details::ListNode<Byte*>>>
class MemoryManager
{
	public:
		/// The type that the MemoryManager object needs for its internal storage.
		typedef details::ListNode<Byte*> AllocatorValueType;
		static_assert(std::is_same<AllocatorValueType, typename AllocatorType::ValueType>::value,
				"The AllocatorType must allocate details::ListNode<Byte*> objects.");

		/// Constructs the manager from a memory block.
		/// \param address The address of the memory block to manage.
		/// \param Size The size of the memory block to manage.
		/// \param allocator The allocator to use.
		MemoryManager(Byte* address, size_t size, AllocatorType allocator = AllocatorType());

		Byte* allocate(size_t size);

		void deallocate(Byte* address);

		void deallocate(Byte* address, size_t size);

	private:
		typedef List<Byte*, AllocatorType> BlockList;

		/// The number of bits in a pointer.
		static constexpr size_t _addressSize{sizeof(void*) * 8};

		AllocatorType _allocator;

		/// Array of list of addresses of free blocks.
		/// The index indicate the size of the blocks in the list:
		/// a block in the list at index 4 has a size of 2^4 bytes.
		Array<BlockList, _addressSize> _freeBlocks;

		/// Array of list of addresses of allocated blocks.
		/// \see freeBlocks
		Array<BlockList, _addressSize> _allocatedBlocks;

		static constexpr bool _activateMemoryDump{false};

		/// Registers a chunk of memory, making it available for allocations.
		/// This is not guaranteed that the whole chunk of memory provided
		/// will really be available (maybe only a smaller chunk, rounded
		/// to some multiple of power of two, will be used instead).
		void addMemoryChunk(Byte* baseAddress, size_t size);

		void tryMerge(typename BlockList::iterator blockToMergeIt, size_t index);

		/// \return A valid iterator in _allocatedBlocks[index] in case of success,
		/// _allocatedBlocks[index].end() otherwise.
		typename BlockList::iterator allocateBlock(size_t index);

		void memoryDump() const;

		static constexpr size_t getIndexFromSize(size_t size);

		// TODO replace by std::find
		static typename BlockList::iterator findBlock(BlockList& blockList, Byte* address);
};

template <class AllocatorType>
MemoryManager<AllocatorType>::MemoryManager(Byte* address, size_t size, AllocatorType allocator):
	_allocator{allocator},
	_freeBlocks{allocator},
	_allocatedBlocks{_allocator}
{
	addMemoryChunk(address, size);
}

template <class AllocatorType>
void MemoryManager<AllocatorType>::addMemoryChunk(Byte* baseAddress, size_t size)
{
	// Avoid nullptr in the allocable space
	if(baseAddress == nullptr)
	{
		++baseAddress;
		--size;
	}
	const size_t index{getIndexFromSize(size)};
	_freeBlocks[index].pushBack(baseAddress);
}

template <class AllocatorType>
Byte* MemoryManager<AllocatorType>::allocate(size_t size)
{
	const size_t index{getIndexFromSize(size)};
	typename BlockList::iterator it{allocateBlock(index)};
	if(_activateMemoryDump)
		memoryDump();
	if(it == _allocatedBlocks[index].end())
	{
		out << "Error: MemoryMamanger::allocate: no more memory, nullptr returned\n";
		return nullptr;
	}
	else
		return *it;
}

template <class AllocatorType>
void MemoryManager<AllocatorType>::deallocate(Byte* address)
{
	if(address == nullptr)
		return;

	// Find the block corresponding to the address
	size_t index{0};
	typename BlockList::iterator it;
	while(index < _addressSize)
	{
		it = findBlock(_allocatedBlocks[index], address);
		if(it != _allocatedBlocks[index].end())
			break;
		index++;
	}

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(address);
		tryMerge(_freeBlocks[index].begin(), index);
	}
	else
		out << "Error: MemoryMamanger::deallocate: invalid pointer argument (" << address << ")\n";
	if(_activateMemoryDump)
		memoryDump();
}

template <class AllocatorType>
void MemoryManager<AllocatorType>::deallocate(Byte* address, size_t size)
{
	if(address == nullptr)
		return;

	// Find the block corresponding to the address
	const size_t index{getIndexFromSize(size)};
	typename BlockList::iterator it{findBlock(_allocatedBlocks[index], address)};

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(address);
		tryMerge(_freeBlocks[index].begin(), index);
	}
	else
		out << "Error: MemoryMamanger::deallocate: invalid pointer argument (" << address << ")\n";
	if(_activateMemoryDump)
		memoryDump();
}

template <class AllocatorType>
void MemoryManager<AllocatorType>::tryMerge(typename BlockList::iterator blockToMergeIt, size_t index)
{
	const size_t blockSize{1UL << index};
	for(typename BlockList::iterator it{_freeBlocks[index].begin()}; it != _freeBlocks[index].end(); ++it)
	{
		// If we found a block...
		if(it != blockToMergeIt
			// that is adjacent to the block to merge...
			and static_cast<size_t>(abs(*it - *blockToMergeIt)) == blockSize
			// and that has a size corresponding to index
			and findBlock(_freeBlocks[index], *it) != _freeBlocks[index].end())

		{
			typename BlockList::iterator lowerBlockIt{*it < *blockToMergeIt ? it : blockToMergeIt};
			typename BlockList::iterator upperBlockIt{lowerBlockIt == blockToMergeIt ? it : blockToMergeIt};
			Byte* baseAddress{*lowerBlockIt};
			_freeBlocks[index].erase(lowerBlockIt);
			_freeBlocks[index].erase(upperBlockIt);
			_freeBlocks[index + 1].pushFront(baseAddress);
			// Recursively merge bigger blocks
			tryMerge(_freeBlocks[index + 1].begin(), index + 1);
			break;
		}
	}
}

template <class AllocatorType>
typename MemoryManager<AllocatorType>::BlockList::iterator MemoryManager<AllocatorType>::allocateBlock(size_t index)
{
	// This should never happens (TODO: write an assert instead)
	if(index >= _addressSize)
		return _allocatedBlocks[_addressSize].end();

	if(_freeBlocks[index].empty())
	{
		// If we ask for the biggest block possible, but there is not a free one
		if(index + 1 == _addressSize)
			return _allocatedBlocks[index].end();

		// Try to get a bigger block
		typename BlockList::iterator biggerBlock{allocateBlock(index + 1)};
		// If this is not possible
		if(biggerBlock == _allocatedBlocks[index + 1].end())
			return _allocatedBlocks[index].end();

		// Erase the bigger allocated block
		Byte* baseAddress{*biggerBlock};
		_allocatedBlocks[index + 1].erase(biggerBlock);

		// Create a block containing the second half of biggerBlock
		Byte* midAddress{baseAddress + (1L << index)};
		// Add it to free list
		_freeBlocks[index].pushFront(midAddress);
		// And add the allocated block (the first half of biggerBlock) to the allocated list
		_allocatedBlocks[index].pushFront(baseAddress);
		return _allocatedBlocks[index].begin();
	}
	else
	{
		// Move an element from the free list to the allocated list
		_allocatedBlocks[index].pushFront(_freeBlocks[index].front());
		_freeBlocks[index].popFront();
		return _allocatedBlocks[index].begin();
	}
}

template <class AllocatorType>
constexpr size_t MemoryManager<AllocatorType>::getIndexFromSize(size_t size)
{
	// Test all power of two until one is bigger than size
	// Note that when size == 0, 0 is returned (corresponding
	// to a chunk of size 1) according to C++ ISO standard
	size_t i{0};
	while(size > (1UL << i) and i + 1 <= _addressSize)
		++i;
	return i;
}

template <class AllocatorType>
typename MemoryManager<AllocatorType>::BlockList::iterator MemoryManager<AllocatorType>::findBlock(BlockList& blockList, Byte* address)
{
	typename BlockList::iterator it{blockList.begin()};
	while(*it != address and it != blockList.end())
		++it;
	return it;
}

template <class AllocatorType>
void MemoryManager<AllocatorType>::memoryDump() const
{
	static const char* separator{" | "};
	out << "A = ";
	for(size_t i{0}; i < _addressSize; ++i)
		out << i << " " << _allocatedBlocks[i].size() << separator;
	out << "\nF = ";
	for(size_t i{0}; i < _addressSize; ++i)
		out << i << " " << _freeBlocks[i].size() << separator;
	out << "\n";
}


#endif// MEMORYMANAGER_HPP
