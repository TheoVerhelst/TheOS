#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <std/cstddef>
#include <cpp/allocators/Allocator.hpp>
#include <cpp/containers/List.hpp>
#include <cpp/containers/Array.hpp>

/// Holds some things related to the implementation of the memory management.
/// The memory is implemented with the buddy algorithm.
class MemoryManager
{
	public:
		typedef List<intptr_t> BlockList;
		typedef BlockList::NodeType ToAllocate;

		/// Constructs the manager from a memory block.
		/// \param address The address of the memory block to manage.
		/// \param Size The size of the memory block to manage.
		/// \param allocator The allocator to use for internal data structures.
		MemoryManager(void* address, size_t size, Allocator<BlockList::NodeType>& allocator = Allocator<BlockList::NodeType>::getDefault());

		void* allocate(size_t size, size_t alignment = 0UL);

		void deallocate(void* address);

	private:
		/// Registers a chunk of memory, making it available for allocations.
		/// This is not guaranteed that the whole chunk of memory provided
		/// will really be available (maybe only a smaller chunk, rounded
		/// to some multiple of power of two, will be used instead).
		void addMemoryChunk(void* baseAddress, size_t size);

		void tryMerge(typename BlockList::Iterator blockToMergeIt, size_t index);

		/// \return A valid iterator in _allocatedBlocks[index] in case of success,
		/// _allocatedBlocks[index].end() otherwise.
		typename BlockList::Iterator allocateBlock(size_t index);

		static inline intptr_t getAlignedAddress(typename BlockList::Iterator blockIt, size_t alignment);

		static typename BlockList::Iterator findBlock(BlockList& blockList, intptr_t address, size_t index);

		/// The number of bits in a pointer.
		static constexpr size_t _addressSize{sizeof(intptr_t) * 8};

		/// Array of list of addresses of free blocks.
		/// The index indicate the size of the blocks in the list:
		/// a block in the list at index 4 has a size of 2^4 bytes.
		Array<BlockList, _addressSize> _freeBlocks;

		/// Array of list of addresses of allocated blocks.
		/// \see freeBlocks
		Array<BlockList, _addressSize> _allocatedBlocks;

		static constexpr intptr_t _nullPointer{reinterpret_cast<intptr_t>(nullptr)};
};



#endif // MEMORYMANAGER_HPP
