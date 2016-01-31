#include <memory.hpp>

void* operator new(size_t size)
{
	const size_t index{getIndexFromSize(size)};
	details::MemoryBlock* block{getBlock(index)};
	if(block == nullptr)
		return nullptr;
	return block->address;
}

void operator delete(void* address)
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

void operator delete[](void* address)
{

}

namespace details
{

MemoryBlock* MemoryBlock::allocate()
{
	const size_t blockIndex{usedMemoryBlocks->find(false)};
	usedMemoryBlocks->set(blockIndex);
	return &memoryBlocksArray[blockIndex];
}

void MemoryBlock::free() const
{
	const size_t blockIndex{this - memoryBlocksArray};
	usedMemoryBlocks->reset(blockIndex);
}

void MemoryBlock::addToList(MemoryBlock** blockArray, size_t index)
{
	previous = nullptr;
	next = blockArray[index];
	if(next != nullptr)
		next->previous = this;
	blockArray[index] = this;
}

void MemoryBlock::removeFromList()
{
	if(next != nullptr)
		next->previous = previous;
	if(previous != nullptr)
		previous->next = next;
}

void MemoryBlock::tryMerge(MemoryBlock** blockArray, size_t index)
{
	const size_t blockSize{1 << index};
	for(MemoryBlock* otherBlock{blockArray[index]}; otherBlock != nullptr; otherBlock = otherBlock->next)
	{
		// If we found another block adjacent to this
		if(otherBlock != this and abs(otherBlock->address - address) == blockSize)
		{
			// Ensure that otherBlock has a size corresponding to index
			if(findBlock(blockArray, index, otherBlock->address) != nullptr)
			{
				MemoryBlock* lowerBlock{otherBlock->address < address ? otherBlock : this};
				MemoryBlock* upperBlock{lowerBlock == this ? otherBlock : this};
				lowerBlock->removeFromList();
				upperBlock->removeFromList();
				lowerBlock->addToList(blockArray, index + 1)
				upperBlock->free();
			}
			break;
		}
	}
}

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
	// Test all power of two until one is bigger than size
	// Note that when size == 0, 0 is returned (corresponding
	// to a chunk of size 1) according to C++ ISO standard
	size_t i{0};
	while(size > (1 << i))
		++i;
	return i;
}

MemoryBlock* findBlock(MemoryBlock** blockArray, size_t index, void* address)
{
	for(MemoryBlock* block{blockArray[index]}; block != nullptr; block = block->next)
		if(block->address == address)
			return block;
	return nullptr;
}

}
