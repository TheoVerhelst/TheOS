#include <memory.hpp>

void* operator new(size_t size)
{
	const size_t index{getIndexFromSize(size)};
	details::MemoryBlock* block{getBlock(index)};
	if(block == nullptr)
		return nullptr;
	return block->address;
}

void  operator delete(void* address)
{
	if(ptr == nullptr)
		return;

	// Find the block corresponding to the address
	size_t index{0};
	details::MemoryBlock* block;
	while(index < addressSize and block == nullptr)
		block = findBlock(allocatedBlocks, index++, address);
	--index;

	if(block == nullptr)
		return nullptr;

	// Add the freed block to the free list
	block->addToList(freeBlocks, index);
	block->tryMerge(freeBlock, index);
}

void* operator new[](std::size_t size)
{
}

void  operator delete[](void* address)
{

}

namespace details
{

MemoryBlock* getBlock(size_t index)
{
	if(index > addressSize)
		return nullptr;

	MemoryBlock* block{freeBlocks[index]};
	if(block == nullptr)
	{
		MemoryBlock* biggerBlock{getBlock(index + 1)};
		if(biggerBlock == nullptr)
			return nullptr;
		biggerBlock->removeFromList();

		// Create a block containing the second half of biggerBlock
		MemoryBlock* midBlock = MemoryBlock::allocate();
		midBlock->address = biggerBlock->address + (1 << index);

		freeBlocks[index] = midBlock;// Add if to free list

		biggerBlock->addToList(allocatedBlocks, index);
		return biggerBlock;
	}
	else
	{
		// Remove the allocated block from the free list
		if(block->next != nullptr)
			block->next->previous = nullptr;
		freeBlocks[index] = block->next;

		block->addToList(allocatedBlocks, index);
		return block;
	}
}

size_t getIndexFromSize(size_t size)
{

}

MemoryBlock* findBlock(MemoryBlock** blockArray, size_t index, void* address)
{
	for(MemoryBlock* block{blockArray[index]}; block != nullptr; block = block->next)
		if(block->address == address)
			return block;
	return nullptr;
}

void MemoryBlock::tryMerge(MemoryBlock** blockArray, size_t index)
{
	for(MemoryBlock* otherBlock{blockArray[index]}; otherBlock != nullptr; otherBlock = otherBlock->next)
	{
		// If we found another block adjacent to this and that begin at (this +- 2^index)
		if(otherBlock != this and (abs(otherBlock->address - address) == (1 << index)))
		{
			// Ensure that otherBlock has a size corresponding to index
			if(findBlock(blockArray, index, otherBlock->address) != nullptr)
			{
				MemoryBlock* lowerBlock{otherBlock->address < address ? otherBlock : this};
				MemoryBlock* upperBlock{lowerBlock == otherBlock ? this : otherBlock};
				if(lowerBlock->previous != nullptr)
					lowerBlock->previous->next = upperBlock->next;
				if(upperBlock->next != nullptr)
					upperBlock->next->previous = lowerBlock->previous;

				// Add the new block to the upper block list
				addBlockToList(blockArray, lowerBlock, index + 1)

				// Free the unused block info
				upperBlock->free();
			}
			break;
		}
	}
}

void addBlockToList(MemoryBlock** blockArray, MemoryBlock* block, size_t index)
{
	block->previous = nullptr;
	block->next = blockArray[index];
	if(block->next != nullptr)
		block->next->previous = block;
	blockArray[index] = block;
}
void removeBlockFromList(MemoryBlock* block)
{
	if(block->next != nullptr)
		block->next->previous = block->previous;
	if(block->previous != nullptr)
		block->previous->next = block->next;
}

}
