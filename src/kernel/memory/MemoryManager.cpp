#include <cpp/math.hpp>
#include <cpp/algo.hpp>
#include <cpp/log.hpp>
#include <kernel/memory/MemoryManager.hpp>

MemoryManager::MemoryManager(void* address, size_t size, Allocator<BlockList::NodeType>& allocator):
	_freeBlocks{allocator},
	_allocatedBlocks{allocator}
{
	addMemoryChunk(address, size);
}

void* MemoryManager::allocate(size_t size, size_t alignment)
{
	const size_t index{getIndexFromSize(size + alignment)};
	intptr_t result{_nullPointer};
	typename BlockList::Iterator it{allocateBlock(index)};

	if(_activateMemoryDump)
		memoryDump();
	if(it == _allocatedBlocks[index].end())
		LOG(Severity::Error) << "no more memory, nullptr returned\n";
	else
		result = getAlignedAddress(it, alignment);

	LOG(Severity::Info) << "found address " << result << "\n";
	STOP();
	return reinterpret_cast<void*>(result);
}

void MemoryManager::deallocate(void* address)
{
	intptr_t addressInt{reinterpret_cast<intptr_t>(address)};

	if(addressInt == _nullPointer)
		return;

	// Find the block corresponding to the address
	size_t index{0};
	typename BlockList::Iterator it{_allocatedBlocks[index].end()};
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
		LOG(Severity::Error) << "invalid pointer argument (" << address << ")\n";
	if(_activateMemoryDump)
		memoryDump();
}

void MemoryManager::deallocate(void* address, size_t size)
{
	intptr_t addressInt{reinterpret_cast<intptr_t>(address)};

	if(addressInt == _nullPointer)
		return;

	// Find the block corresponding to the address
	const size_t index{getIndexFromSize(size)};
	typename BlockList::Iterator it{findBlock(_allocatedBlocks[index], addressInt, index)};

	if(it != _allocatedBlocks[index].end())
	{
		// Add the freed block to the free list
		_allocatedBlocks[index].erase(it);
		_freeBlocks[index].pushFront(addressInt);
		tryMerge(_freeBlocks[index].begin(), index);
	}
	else
		LOG(Severity::Error) << "invalid pointer argument (" << address << ")\n";
	if(_activateMemoryDump)
		memoryDump();
}

void MemoryManager::addMemoryChunk(void* baseAddress, size_t size)
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

void MemoryManager::tryMerge(typename BlockList::Iterator blockToMergeIt, size_t index)
{
	const size_t blockSize{1UL << index};
	for(auto it(_freeBlocks[index].begin()); it != _freeBlocks[index].end(); ++it)
	{
		// If we found a block...
		if(it != blockToMergeIt
			// that is adjacent to the block to merge...
			and math::abs(*it - *blockToMergeIt) == static_cast<intptr_t>(blockSize)
			// and that has a size corresponding to index
			and findBlock(_freeBlocks[index], *it, index) != _freeBlocks[index].end())

		{
			typename BlockList::Iterator lowerBlockIt{*it < *blockToMergeIt ? it : blockToMergeIt};
			typename BlockList::Iterator upperBlockIt{lowerBlockIt == blockToMergeIt ? it : blockToMergeIt};
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

typename MemoryManager::BlockList::Iterator MemoryManager::allocateBlock(size_t index)
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
		LOG(Severity::Info) << "trying to push front\n";
		_allocatedBlocks[index].pushFront(_freeBlocks[index].front());
		_freeBlocks[index].popFront();
		return _allocatedBlocks[index].begin();
	}
}

constexpr size_t MemoryManager::getIndexFromSize(size_t size)
{
	// Test all power of two until one is bigger than size
	// Note that when size == 0, 0 is returned (corresponding
	// to a chunk of size 1) according to C++ ISO standard
	size_t i{0};
	while(size > (1UL << i) and i + 1 <= _addressSize)
		++i;
	return i;
}

typename MemoryManager::BlockList::Iterator MemoryManager::findBlock(BlockList& blockList, intptr_t address, size_t index)
{
	return algo::find(blockList.begin(), blockList.end(), [index, address](intptr_t block)
	{
		return address >= block and address < static_cast<intptr_t>(block + (1UL << index));
	});
}

inline intptr_t MemoryManager::getAlignedAddress(typename BlockList::Iterator blockIt, size_t alignment)
{
	if(alignment > 0)
	{
		const size_t offset{alignment - (*blockIt % alignment)};
		return *blockIt + offset;
	}
	else
		return *blockIt;
}

void MemoryManager::memoryDump() const
{
	static const char* separator{" | "};
	LOG(Severity::Info) << "A = ";
	for(size_t i{0}; i < _addressSize; ++i)
		LOG(Severity::Info) << i << " " << _allocatedBlocks[i].size() << separator;
	LOG(Severity::Info) << "\nF = ";
	for(size_t i{0}; i < _addressSize; ++i)
		LOG(Severity::Info) << i << " " << _freeBlocks[i].size() << separator;
	LOG(Severity::Info) << "\n";
}
