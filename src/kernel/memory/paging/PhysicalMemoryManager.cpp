#include <std/cstdint>
#include <cpp/Printer.hpp>
#include <kernel/memory/paging/PhysicalMemoryManager.hpp>

namespace paging
{

PhysicalMemoryManager::PhysicalMemoryManager()
{
	if(not (multiboot::multibootInfoAddress->_flags & multiboot::InfoAvailable::mmap))
		return;

	parseMemoryMap();
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
		out << "PhysicalMemoryManager::freeFrame: "
			<< (free ? "free" : "allocat")
			<< "ing a frame that is not 4k-aligned ("
			<< intAddress << ")\n";
		return;
	}

	size_t index{(intAddress - lowerMemoryLimit) / paging::pageSize};

	if(index < _freeFrames.size())
		_freeFrames.set(index, free);
}

void PhysicalMemoryManager::parseMemoryMap()
{
	multiboot::MemoryRegion* region{multiboot::multibootInfoAddress->_mmap_addr};
	const size_t memoryMapSize{multiboot::multibootInfoAddress->_mmap_length};
	uintptr_t intAddress{reinterpret_cast<uintptr_t>(region)};
	const uintptr_t memoryMapUpperBound{intAddress + memoryMapSize};

	// While there is yet elements in the map
	while(intAddress < memoryMapUpperBound)
	{
		if(region->_type == multiboot::MemoryRegion::_validType)
			freeMemoryRegion(*region);

		intAddress += region->_size + sizeof(region->_size);
		region = reinterpret_cast<multiboot::MemoryRegion*>(intAddress);
	}
}

void PhysicalMemoryManager::freeMemoryRegion(const multiboot::MemoryRegion& region)
{
	// region.base_addr is 64-bits, get only the first 32 bits
	uintptr_t address{static_cast<uintptr_t>(region._base_addr & UINT64_C(0xFFFFFFFF))};
	const size_t size{static_cast<size_t>(region._length)};
	// Get the upper bound aligned to 4k (rounded down to the first 4k multiple)
	uintptr_t upperBound{alignDown(address + size)};
	address = alignUp(address);

	// TODO replace i by frame, do not divide by pageSize all the way
	for(size_t i{address / paging::pageSize}; i < upperBound / paging::pageSize; ++i)
	{
		const uintptr_t frame{i * paging::pageSize};
		// FIXME: If this condition is removed, the boot sequence crashes
		// This may be a special area not told by the BIOS
		if(frame <= 0x1D5000 or frame > 0x250000)
			freeFrame(reinterpret_cast<void*>(frame));
	}
}

} // namespace paging
