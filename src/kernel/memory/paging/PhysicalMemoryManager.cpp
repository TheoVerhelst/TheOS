#include <std/cstdint>
#include <cpp/log.hpp>
#include <kernel/memory/paging/PhysicalMemoryManager.hpp>

namespace paging
{

PhysicalMemoryManager::PhysicalMemoryManager(const MemoryMap& memoryMap)
{
	for(const auto& region : memoryMap)
		freeMemoryRegion(region);
}

void* PhysicalMemoryManager::allocateFrame()
{
	size_t index{_freeFrames.find(true)};
	// The bitmap doesn't includes the lower memory limit, we have to take this
	// into account
	if(index == _freeFrames._invalidIndex)
		return nullptr;
	else
	{
		_freeFrames.reset(index);
		return reinterpret_cast<void*>(lowerMemoryLimit + index * paging::pageSize);
	}
}

void PhysicalMemoryManager::allocateFrame(void* address)
{
	setFrame(address, false);
}

void PhysicalMemoryManager::freeFrame(void* address)
{
	setFrame(address, true);
}

void PhysicalMemoryManager::setFrame(void* address, bool free)
{
	intptr_t intAddress{reinterpret_cast<intptr_t>(address)};

	// If the address is not 4k-aligned
	if((intAddress & 0xFFF) != 0)
	{
		LOG(Severity::Error) << (free ? "free" : "allocat")
			<< "ing a frame that is not 4k-aligned (" << intAddress << ")\n";
		return;
	}

	size_t index{(intAddress - lowerMemoryLimit) / paging::pageSize};

	if(index < _freeFrames.size())
		_freeFrames.set(index, free);
}

void PhysicalMemoryManager::freeMemoryRegion(const MemoryRegion& region)
{
	// region.base_addr is 64-bits, get only the first 32 bits
	uintptr_t address{reinterpret_cast<uintptr_t>(region._address)};
	const size_t size{region._size};
	// Get the upper bound aligned to 4k (rounded down to the first 4k multiple)
	uintptr_t upperBound{alignDown(address + size)};
	address = alignUp(address);

	// TODO replace i by frame, do not divide by pageSize all the way
	for(size_t i{address / paging::pageSize}; i < upperBound / paging::pageSize; ++i)
		freeFrame(reinterpret_cast<void*>(i * paging::pageSize));
}

} // namespace paging
