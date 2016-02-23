#include <kernel/memory/MemoryManager.hpp>
#include <math.hpp>
#include <Printer.hpp>

BitSet<MemoryManager::_maxBlocksNumber> MemoryManager::ListNodeAllocator::_usedListNodes;
MemoryManager::ListNodeAllocator::valueType MemoryManager::ListNodeAllocator::_listNodesArray[MemoryManager::_maxBlocksNumber];

MemoryManager::MemoryManager(MemoryRegion* address, size_t size, size_t neededHeapSize)
{
	uintptr_t rawAddress{reinterpret_cast<uintptr_t>(address)};
	const uintptr_t upperAddress{rawAddress + size};
	while(rawAddress < upperAddress)
	{
		if(address->type == 1 and static_cast<size_t>(address->length) >= neededHeapSize)
		{
			void* baseAddress{reinterpret_cast<void*>(address->base_addr)};
			addMemoryChunk(baseAddress, neededHeapSize);
			out << "Allocated heap of size " << neededHeapSize/1000 << " Ko starting at " << baseAddress << "\n";
			return;
		}
		rawAddress += address->size + sizeof(address->size);
		address = reinterpret_cast<MemoryRegion*>(rawAddress);
	}
}

void MemoryManager::addMemoryChunk(void* baseAddress, size_t size)
{
	intptr_t convertedBaseAddress{reinterpret_cast<intptr_t>(baseAddress)};
	// Avoid nullptr in the allocable space
	if(baseAddress == nullptr)
	{
		++convertedBaseAddress;
		--size;
	}
	const size_t index{getIndexFromSize(size)};
	_freeBlocks[index].pushBack(convertedBaseAddress);
}

void* MemoryManager::allocate(size_t size)
{
	const size_t index{getIndexFromSize(size)};
	blockIt it{allocateBlock(index)};
	if(it == _allocatedBlocks[index].end())
	{
		out << "Error: MemoryMamanger::allocate: no more memory, nullptr returned\n";
		return nullptr;
	}
	else
		return reinterpret_cast<void*>(*it);
}

void MemoryManager::deallocate(void* address)
{
	if(address == nullptr)
		return;

	const intptr_t convertedAddress{reinterpret_cast<intptr_t>(address)};

	// Find the block corresponding to the address
	size_t index{0};
	blockIt it;
	while(index < _addressSize)
		it = findBlock(_allocatedBlocks[index++], convertedAddress);
	--index;

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(convertedAddress);
		tryMerge(_freeBlocks[index].begin(), index);
	}
	else
		out << "Error: MemoryMamanger::deallocate: invalid pointer argument (" << address << ")\n";
}

void MemoryManager::deallocate(void* address, size_t size)
{
	if(address == nullptr)
		return;

	const intptr_t convertedAddress{reinterpret_cast<intptr_t>(address)};

	// Find the block corresponding to the address
	size_t index{getIndexFromSize(size)};
	blockIt it{findBlock(_allocatedBlocks[index], convertedAddress)};

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(convertedAddress);
		tryMerge(_freeBlocks[index].begin(), index);
	}
	else
		out << "Error: MemoryMamanger::deallocate: invalid pointer argument (" << address << ")\n";
}


MemoryManager::ListNodeAllocator::pointer MemoryManager::ListNodeAllocator::allocate()
{
	const size_t blockIndex{_usedListNodes.find(false)};
	if(blockIndex == ~0UL)
		return nullptr;
	_usedListNodes.set(blockIndex);
	return &_listNodesArray[blockIndex];
}

void MemoryManager::ListNodeAllocator::deallocate(MemoryManager::ListNodeAllocator::pointer pointer)
{
	const size_t blockIndex{static_cast<size_t>(pointer - _listNodesArray)};
	if(blockIndex < _maxBlocksNumber)
		_usedListNodes.reset(blockIndex);
}

void MemoryManager::tryMerge(blockIt blockToMergeIt, size_t index)
{
	const size_t blockSize{1UL << index};
	for(blockIt it{_freeBlocks[index].begin()}; it != _freeBlocks[index].end(); ++it)
	{
		// If we found a block...
		if(it != blockToMergeIt
			// that is adjacent to the block to merge...
			and static_cast<size_t>(abs(*it - *blockToMergeIt)) == blockSize
			// and that has a size corresponding to index
			and findBlock(_freeBlocks[index], *it) != _freeBlocks[index].end())

		{
			blockIt lowerBlockIt{*it < *blockToMergeIt ? it : blockToMergeIt};
			blockIt upperBlockIt{lowerBlockIt == blockToMergeIt ? it : blockToMergeIt};
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

MemoryManager::blockIt MemoryManager::allocateBlock(size_t index)
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
		blockIt biggerBlock{allocateBlock(index + 1)};
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

size_t MemoryManager::getIndexFromSize(size_t size)
{
	// Test all power of two until one is bigger than size
	// Note that when size == 0, 0 is returned (corresponding
	// to a chunk of size 1) according to C++ ISO standard
	size_t i{0};
	while(size > (1UL << i) and i + 1 <= _addressSize)
		++i;
	return i;
}

MemoryManager::blockIt MemoryManager::findBlock(List<intptr_t, ListNodeAllocator>& blockList, intptr_t address)
{
	blockIt it{blockList.begin()};
	while(*it != address and it != blockList.end())
		++it;
	return it;
}

void MemoryManager::memoryDump() const
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
