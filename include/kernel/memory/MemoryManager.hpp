#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <BitSet.hpp>
#include <List.hpp>
#include <boot/MultibootInfo.hpp>

/// Holds some things related to the implementation of the memory management.
/// The memory is implemented with the buddy algorithm.
class MemoryManager
{
	public:
		/// Constructs the manager from a list of MemoryRegion.
		/// The arguments match to the ones provided by the multiboot info
		/// structure.
		/// \param address The address of the first MemoryRegion structure.
		/// \param Size the number of memory regions.
		/// \param neededHeapSize The minimum size that the kernel want for its heap.
		MemoryManager(MemoryRegion* address, size_t size, size_t neededHeapSize);

		void* allocate(size_t size);

		void deallocate(void* address);

		void deallocate(void* address, size_t size);

	private:
		/// The number of bits of an address.
		static constexpr size_t _addressSize{sizeof(void*) * 8};

		/// Maximum number of blocks. Even if the memory is not full,
		/// memory allocation will fail if there is too much blocks.
		/// The limit of blocks must be static and reserve too much room
		/// to blocks information will result in bigger kernel.
		static constexpr size_t _maxBlocksNumber{1 << 16};

		/// Class that manages the list nodes used to manage the kernel's heap.
		/// All nodes that are in the lists that manages the kernel's heap
		/// (freeBlocks and allocatedBlocks) are in fact stored in the instance
		/// pf this class.
		class ListNodeAllocator
		{
			public:
				typedef details::ListNode<intptr_t> valueType;
				typedef valueType* pointer;

				pointer allocate();
				void deallocate(pointer pointer);

			private:
				/// Indicates in memoryBlocksArray wich nodes are currently
				/// allocated by one of the two lists (freeBlocks and
				/// allocatedBlocks). This is the primary memory allocation
				/// scfaheme used to implements the real memory allocation.
				static BitSet<_maxBlocksNumber> _usedListNodes;

				/// An array of list nodes. This is where all data
				/// about memory allocation is stored, freeBlocks and
				/// allocatedBlocks hold list nodes that are elements of this
				/// array.
				static valueType _listNodesArray[_maxBlocksNumber];
		};

		typedef List<intptr_t, ListNodeAllocator>::iterator blockIt;

		/// Array of list of addresses of free blocks.
		/// The index indicate the size of the blocks in the list:
		/// a block in the list at index 4 has a size of 2^4 bytes.
		List<intptr_t, ListNodeAllocator> _freeBlocks[_addressSize];

		/// Array of list of addresses of allocated blocks.
		/// \see freeBlocks
		List<intptr_t, ListNodeAllocator> _allocatedBlocks[_addressSize];

		/// Instance of the allocator used for this MemoryManager.
		ListNodeAllocator _allocator;

		/// Registers a chunk of memory, making it available for allocations.
		/// This is not guaranteed that the whole chunk of memory provided
		/// will really be available (maybe only a smaller chunk, rounded
		/// to some multiple of power of two, will be used instead).
		void addMemoryChunk(void* baseAddress, size_t size);

		void tryMerge(blockIt blockToMergeIt, size_t index);

		/// \return A valid iterator in _allocatedBlocks[index] in case of success,
		/// _allocatedBlocks[index].end() otherwise.
		blockIt allocateBlock(size_t index);

		// TODO try to add constexpr
		static size_t getIndexFromSize(size_t size);

		// TODO replace by std::find
		static blockIt findBlock(List<intptr_t, ListNodeAllocator>& blockList, intptr_t address);

		void memoryDump() const;
};

#endif// MEMORYMANAGER_HPP
