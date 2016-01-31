#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <BitSet.hpp>

void* operator new(size_t size) throw();
void operator delete(void* address) throw();
void* operator new[](size_t size) throw();
void operator delete[](void* address) throw();

/// Holds all things related to the implementation of the memory management.
/// The memory is implemented with the buddy algorithm.
class MemoryManager
{
	public:
		/// The number of bits of an address.
		static constexpr size_t addressSize{sizeof(void*) * 8};

		/// Maximum number of blocks. Even if the memory is not full,
		/// memory allocation will fail if there is too much blocks.
		/// The limit of blocks must be static and reserve too much room
		/// to blocks information will result in bigger kernel.
		static constexpr size_t maxBlocksNumber{1 << 16};

		/// Element of a linked list of free block.
		/// The size of the free block is implicitly given
		/// by its position in the free blocks list.
		///
		class MemoryBlock
		{
			public:
				void* address = nullptr;        ///< Address of the first byte of the block in memory.
				MemoryBlock* next = nullptr;    ///< Next block in the list.
				MemoryBlock* previous = nullptr;///< Previous block in the memory.

				static MemoryBlock* allocate();
				void free() const;
				void addToList(MemoryBlock** blockArray, size_t index);
				void removeFromList();
				void tryMerge(MemoryBlock** blockArray, size_t index);
		};

		/// Array of pointers to free blocks.
		/// The index indicate the size of the blocks in the list:
		/// a block at index 4 has a size of 2^4 bytes.
		static MemoryBlock* freeBlocks[addressSize];

		/// Array of pointers to allocated blocks.
		/// The index indicate the size of the blocks in the list:
		/// a block at index 4 has a size of 2^4 bytes.
		static MemoryBlock* allocatedBlocks[addressSize];

		/// An array of MemoryBlock objects. This is where all data
		/// about memory allocation is stored, freeBlocks and allocatedBlocks
		/// hold pointers that point to elements of this array.
		static MemoryBlock memoryBlocksArray[maxBlocksNumber];

		/// Indicates in memoryBlocksArray wich elements are currently used in
		/// the two lists (freeBlocks and allocatedBlocks).
		/// This is the primary memory allocation scheme used to implements
		/// the real memory allocation.
		static BitSet<maxBlocksNumber> usedMemoryBlocks;

		static MemoryBlock* getBlock(size_t index);

		static size_t getIndexFromSize(size_t size);

		static MemoryBlock* findBlock(MemoryBlock** blockArray, size_t index, void* address);
};

#endif// MEMORY_HPP
