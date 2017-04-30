#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <std/cstddef>
#include <std/type_traits>
#include <kernel/memory/Byte.hpp>
#include <cpp/memory.hpp>
#include <cpp/math.hpp>
#include <cpp/List.hpp>
#include <cpp/Printer.hpp>
#include <cpp/Array.hpp>

/// \addtogroup Kernel
/// \{

/// Holds some things related to the implementation of the memory management.
/// The memory is implemented with the buddy algorithm.
template <class AllocatorType = Allocator<details::ListNode<intptr_t>>>
class MemoryManager
{
	public:
		/// The type that the MemoryManager object needs for its internal storage.
		typedef details::ListNode<intptr_t> AllocatorValueType;
		static_assert(std::is_same<AllocatorValueType, typename AllocatorType::ValueType>::value,
				"The AllocatorType must allocate details::ListNode<void*> objects.");

		/// Constructs the manager.
		/// \param allocator The allocator to use.
		MemoryManager(AllocatorType allocator = AllocatorType());

		/// Constructs the manager from a memory block.
		/// \param address The address of the memory block to manage.
		/// \param Size The size of the memory block to manage.
		/// \param allocator The allocator to use.
		MemoryManager(void* address, size_t size, AllocatorType allocator = AllocatorType());

		void* allocate(size_t size, size_t alignment = 0UL);

		void deallocate(void* address);

		void deallocate(void* address, size_t size);

		/// Registers a chunk of memory, making it available for allocations.
		/// This is not guaranteed that the whole chunk of memory provided
		/// will really be available (maybe only a smaller chunk, rounded
		/// to some multiple of power of two, will be used instead).
		void addMemoryChunk(void* baseAddress, size_t size);

	private:
		typedef List<intptr_t, AllocatorType> BlockList;

		/// The number of bits in a pointer.
		static constexpr size_t _addressSize{sizeof(intptr_t) * 8};

		AllocatorType _allocator;

		/// Array of list of addresses of free blocks.
		/// The index indicate the size of the blocks in the list:
		/// a block in the list at index 4 has a size of 2^4 bytes.
		Array<BlockList, _addressSize> _freeBlocks;

		/// Array of list of addresses of allocated blocks.
		/// \see freeBlocks
		Array<BlockList, _addressSize> _allocatedBlocks;

		static constexpr bool _activateMemoryDump{false};

		static constexpr intptr_t _nullPointer{reinterpret_cast<intptr_t>(nullptr)};

		void tryMerge(typename BlockList::iterator blockToMergeIt, size_t index);

		/// \return A valid iterator in _allocatedBlocks[index] in case of success,
		/// _allocatedBlocks[index].end() otherwise.
		typename BlockList::iterator allocateBlock(size_t index);

		static inline intptr_t getAlignedAddress(typename BlockList::iterator blockIt, size_t alignment);

		void memoryDump() const;

		static constexpr size_t getIndexFromSize(size_t size);

		// TODO replace by std::find
		static typename BlockList::iterator findBlock(BlockList& blockList, intptr_t address, size_t index);
};

template <class AllocatorType>
MemoryManager<AllocatorType>::MemoryManager(AllocatorType allocator):
	_allocator{allocator},
	_freeBlocks{allocator},
	_allocatedBlocks{_allocator}
{
}

template <class AllocatorType>
MemoryManager<AllocatorType>::MemoryManager(void* address, size_t size, AllocatorType allocator):
	MemoryManager{allocator}
{
	addMemoryChunk(address, size);
}

template <class AllocatorType>
void MemoryManager<AllocatorType>::addMemoryChunk(void* baseAddress, size_t size)
{
	intptr_t baseAddressInt{reinterpret_cast<intptr_t>(baseAddress)};
	// Avoid nullptr in the allocable space
	if(baseAddressInt == _nullPointer and size > 0)
	{
		++baseAddressInt;
		--size;
	}
	const size_t index{getIndexFromSize(size)};
	_freeBlocks[index].pushBack(baseAddressInt);
}

template <class AllocatorType>
void* MemoryManager<AllocatorType>::allocate(size_t size, size_t alignment)
{
	const size_t index{getIndexFromSize(size + alignment)};
	intptr_t result{_nullPointer};
	typename BlockList::iterator it{allocateBlock(index)};

	if(_activateMemoryDump)
		memoryDump();
	if(it == _allocatedBlocks[index].end())
		out << "Error: MemoryMamanger::allocate: no more memory, nullptr returned\n";
	else
		result = getAlignedAddress(it, alignment);

	return reinterpret_cast<void*>(result);
}

template <class AllocatorType>
void MemoryManager<AllocatorType>::deallocate(void* address)
{
	intptr_t addressInt{reinterpret_cast<intptr_t>(address)};

	if(addressInt == _nullPointer)
		return;

	// Find the block corresponding to the address
	size_t index{0};
	typename BlockList::iterator it;
	while(index < _addressSize)
	{
		it = findBlock(_allocatedBlocks[index], addressInt, index);
		if(it != _allocatedBlocks[index].end())
			break;
		index++;
	}

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(addressInt);
		tryMerge(_freeBlocks[index].begin(), index);
	}
	else
		out << "Error: MemoryMamanger::deallocate: invalid pointer argument (" << address << ")\n";
	if(_activateMemoryDump)
		memoryDump();
}

template <class AllocatorType>
void MemoryManager<AllocatorType>::deallocate(void* address, size_t size)
{
	intptr_t addressInt{reinterpret_cast<intptr_t>(address)};

	if(addressInt == _nullPointer)
		return;

	// Find the block corresponding to the address
	const size_t index{getIndexFromSize(size)};
	typename BlockList::iterator it{findBlock(_allocatedBlocks[index], addressInt, index)};

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(addressInt);
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
	for(auto it(_freeBlocks[index].begin()); it != _freeBlocks[index].end(); ++it)
	{
		// If we found a block...
		if(it != blockToMergeIt
			// that is adjacent to the block to merge...
			and abs(*it - *blockToMergeIt) == static_cast<intptr_t>(blockSize)
			// and that has a size corresponding to index
			and findBlock(_freeBlocks[index], *it, index) != _freeBlocks[index].end())

		{
			typename BlockList::iterator lowerBlockIt{*it < *blockToMergeIt ? it : blockToMergeIt};
			typename BlockList::iterator upperBlockIt{lowerBlockIt == blockToMergeIt ? it : blockToMergeIt};
			intptr_t baseAddress{*lowerBlockIt};
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
		// If we ask for the biggest block possible, but there is no free one
		if(index + 1 == _addressSize)
			return _allocatedBlocks[index].end();

		// Try to get a bigger block
		auto biggerBlock(allocateBlock(index + 1));
		// If this is not possible
		if(biggerBlock == _allocatedBlocks[index + 1].end())
			return _allocatedBlocks[index].end();

		// Erase the bigger allocated block
		intptr_t baseAddress{*biggerBlock};
		_allocatedBlocks[index + 1].erase(biggerBlock);

		// Create a block containing the second half of biggerBlock
		intptr_t midAddress{baseAddress + (1L << index)};
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
typename MemoryManager<AllocatorType>::BlockList::iterator MemoryManager<AllocatorType>::findBlock(BlockList& blockList, intptr_t address, size_t index)
{
	typename BlockList::iterator it{blockList.begin()};
	const size_t blockSize{1UL << index};
	// Loop while the address is not in the block pointed by it
	while((address < *it or address >= static_cast<intptr_t>(*it + blockSize)) and it != blockList.end())
		++it;
	return it;
}

template <class AllocatorType>
inline intptr_t MemoryManager<AllocatorType>::getAlignedAddress(typename BlockList::iterator blockIt, size_t alignment)
{
	if(alignment > 0)
	{
		const size_t offset{alignment - (*blockIt % alignment)};
		return *blockIt + offset;
	}
	else
		return *blockIt;
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

/// \}

#endif// MEMORYMANAGER_HPP
