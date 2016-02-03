#include <memory.hpp>
#include <math.hpp>
#include <Printer.hpp>

extern MemoryManager kernelHeapMamanger;

void* operator new(size_t size) throw()
{
	return kernelHeapMamanger.allocate(size);
}

void operator delete(void* address) throw()
{
	kernelHeapMamanger.deallocate(address);
}

void operator delete(void* address, size_t size) throw()
{
	kernelHeapMamanger.deallocate(address, size);
}

void* operator new[](size_t size) throw()
{
	return operator new(size);
}

void operator delete[](void* address) throw()
{
	operator delete(address);
}

void operator delete[](void* address, size_t size) throw()
{
	operator delete(address, size);
}

BitSet<MemoryManager::_maxBlocksNumber> MemoryManager::ListNodeAllocator::_usedListNodes;
MemoryManager::ListNodeAllocator::valueType MemoryManager::ListNodeAllocator::_listNodesArray[MemoryManager::_maxBlocksNumber];

template <class T>
T* Allocator<T>::allocate()
{
	return new T;
}

template <class T>
void Allocator<T>::deallocate(T* pointer)
{
	delete pointer;
}

void MemoryManager::addMemoryChunk(void* baseAddress, size_t size)
{
	const size_t index{getIndexFromSize(size)};
	_freeBlocks[index].pushBack(baseAddress);
}

void* MemoryManager::allocate(size_t size)
{
	const size_t index{getIndexFromSize(size)};
	blockIt it{getBlock(index)};
	if(it == _allocatedBlocks[index].end() or *it == nullptr)
	{
		out << "Error: MemoryMamanger::allocate: no more memory, nullptr returned\n";
		return nullptr;
	}
	else
		return *it;
}

void MemoryManager::deallocate(void* address)
{
	if(address == nullptr)
		return;

	// Find the block corresponding to the address
	size_t index{0};
	blockIt it;
	while(index < _addressSize)
		it = findBlock(_allocatedBlocks[index++], address);
	--index;

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(address);
		tryMerge(_freeBlocks[index].begin(), index);
	}
	else
		out << "Error: MemoryMamanger::deallocate: invalid pointer argument (" << address << ")\n";
}

void MemoryManager::deallocate(void* address, size_t size)
{
	if(address == nullptr)
		return;

	// Find the block corresponding to the address
	size_t index{getIndexFromSize(size)};
	blockIt it{findBlock(_allocatedBlocks[index], address)};

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(address);
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
			and static_cast<size_t>(abs(static_cast<char*>(*it) - static_cast<char*>(*blockToMergeIt))) == blockSize
			// and that has a size corresponding to index
			and findBlock(_freeBlocks[index], *it) != _freeBlocks[index].end())

		{
			blockIt lowerBlockIt{*it < *blockToMergeIt ? it : blockToMergeIt};
			blockIt upperBlockIt{lowerBlockIt == blockToMergeIt ? it : blockToMergeIt};
			void* baseAddress{*lowerBlockIt};
			_freeBlocks[index].erase(lowerBlockIt);
			_freeBlocks[index].erase(upperBlockIt);
			_freeBlocks[index + 1].pushFront(baseAddress);
			//Recursively merge bigger blocks
			tryMerge(_freeBlocks[index + 1].begin(), index + 1);
			break;
		}
	}
}

MemoryManager::blockIt MemoryManager::getBlock(size_t index)
{
	//This should never happens (TODO: write an assert instead)
	if(index >= _addressSize)
		return _allocatedBlocks[_addressSize].end();

	if(_freeBlocks[index].empty())
	{
		//If we ask for the biggest block possible, but there is not a free one
		if(index + 1 == _addressSize)
			return _allocatedBlocks[index].end();

		// Try to get a bigger free block
		blockIt biggerBlock{getBlock(index + 1)};
		// If this is not possible
		if(biggerBlock == _allocatedBlocks[index + 1].end())
			return _allocatedBlocks[index].end();

		//Erase the bigger free block
		void* baseAddress{*biggerBlock};
		_freeBlocks[index + 1].erase(biggerBlock);

		// Create a block containing the second half of biggerBlock
		void* midAddress{reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(*biggerBlock) + (1UL << index))};
		// Add if to free list
		_freeBlocks[index].pushFront(midAddress);
		// And add the allocated block (the first half of biggerBlock) to the allocated list
		_allocatedBlocks[index].pushFront(baseAddress);
		return _allocatedBlocks[index].begin();
	}
	else
	{
		blockIt it{_freeBlocks[index].begin()};
		void* address{*it};
		_freeBlocks[index].erase(it);
		_allocatedBlocks[index].pushFront(address);
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

MemoryManager::blockIt MemoryManager::findBlock(List<void*, ListNodeAllocator>& blockList, void* address)
{
	blockIt it{blockList.begin()};
	while(*it != address and it != blockList.end())
		++it;
	return it;
}
