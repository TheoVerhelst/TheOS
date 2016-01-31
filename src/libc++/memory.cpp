#include <memory.hpp>
#include <math.hpp>

MemoryManager::MemoryBlock* MemoryManager::freeBlocks[MemoryManager::addressSize];
MemoryManager::MemoryBlock* MemoryManager::allocatedBlocks[MemoryManager::addressSize];
MemoryManager::MemoryBlock MemoryManager::memoryBlocksArray[MemoryManager::maxBlocksNumber];
BitSet<MemoryManager::maxBlocksNumber> MemoryManager::usedMemoryBlocks;

void* operator new(size_t size) throw()
{
	const size_t index{MemoryManager::getIndexFromSize(size)};
	MemoryManager::MemoryBlock* block{MemoryManager::getBlock(index)};
	if(block == nullptr)
		return nullptr;
	return block->address;
}

void operator delete(void* address) throw()
{
	if(address == nullptr)
		return;

	// Find the block corresponding to the address
	size_t index{0};
	MemoryManager::MemoryBlock* block;
	while(index < MemoryManager::addressSize and block == nullptr)
		block = MemoryManager::findBlock(MemoryManager::allocatedBlocks, index++, address);
	--index;

	if(block != nullptr)
	{
		// Add the freed block to the free list
		block->addToList(MemoryManager::freeBlocks, index);
		block->tryMerge(MemoryManager::freeBlocks, index);
	}
}

void* operator new[](size_t size) throw()
{
	return operator new(size);
}

void operator delete[](void* address) throw()
{
	operator delete(address);
}

MemoryManager::MemoryBlock* MemoryManager::MemoryBlock::allocate()
{
	const size_t blockIndex{usedMemoryBlocks.find(false)};
	usedMemoryBlocks.set(blockIndex);
	return &memoryBlocksArray[blockIndex];
}

void MemoryManager::MemoryBlock::free() const
{
	const size_t blockIndex{static_cast<size_t>(this - memoryBlocksArray)};
	usedMemoryBlocks.reset(blockIndex);
}

void MemoryManager::MemoryBlock::addToList(MemoryManager::MemoryBlock** blockArray, size_t index)
{
	previous = nullptr;
	next = blockArray[index];
	if(next != nullptr)
		next->previous = this;
	blockArray[index] = this;
}

void MemoryManager::MemoryBlock::removeFromList()
{
	if(next != nullptr)
		next->previous = previous;
	if(previous != nullptr)
		previous->next = next;
}

void MemoryManager::MemoryBlock::tryMerge(MemoryManager::MemoryBlock** blockArray, size_t index)
{
	const size_t blockSize{1UL << index};
	for(MemoryBlock* otherBlock{blockArray[index]}; otherBlock != nullptr; otherBlock = otherBlock->next)
	{
		// If we found another block adjacent to this
		if(otherBlock != this)
		{
			long diff = static_cast<char*>(otherBlock->address) - static_cast<char*>(address);
			if((diff > 0 ? diff : -diff) == blockSize)
			{
				// Ensure that otherBlock has a size corresponding to index
				if(findBlock(blockArray, index, otherBlock->address) != nullptr)
				{
					MemoryBlock* lowerBlock{otherBlock->address < address ? otherBlock : this};
					MemoryBlock* upperBlock{lowerBlock == this ? otherBlock : this};
					lowerBlock->removeFromList();
					upperBlock->removeFromList();
					lowerBlock->addToList(blockArray, index + 1);
					upperBlock->free();
				}
				break;
			}
		}
	}
}

MemoryManager::MemoryBlock* MemoryManager::getBlock(size_t index)
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
		midBlock->address = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(biggerBlock->address) + (1 << index));

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

size_t MemoryManager::getIndexFromSize(size_t size)
{
	// Test all power of two until one is bigger than size
	// Note that when size == 0, 0 is returned (corresponding
	// to a chunk of size 1) according to C++ ISO standard
	size_t i{0};
	while(size > (1 << i))
		++i;
	return i;
}

MemoryManager::MemoryBlock* MemoryManager::findBlock(MemoryBlock** blockArray, size_t index, void* address)
{
	for(MemoryBlock* block{blockArray[index]}; block != nullptr; block = block->next)
		if(block->address == address)
			return block;
	return nullptr;
}
