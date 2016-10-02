#include <cstdint>
#include <kernel/memory/PhysicalMemoryManager.hpp>
#include <Printer.hpp>

PhysicalMemoryManager::PhysicalMemoryManager()
{
	if(not (multiboot::multibootInfoAddress->_flags & multiboot::InfoAvailable::mmap))
		return;

	parseMemoryMap();
}

Byte* PhysicalMemoryManager::allocateFrame()
{
	size_t index{_freeFrames.find(true)};
	// The bitmap doesn't includes the lower memory limit, we have to take this
	// into account
	return index == _freeFrames._invalidIndex ? nullptr : paging::lowerMemoryLimit + index * paging::pageSize;
}

void PhysicalMemoryManager::freeFrame(Byte* address)
{
	// If the address is not 4k-aligned
	if((reinterpret_cast<uintptr_t>(address) & 0xFFF) != 0)
		return;

	// FIXME: If this condition is removed, the boot sequence crashes
	// This may be a special area not told by the BIOS
	if(reinterpret_cast<uintptr_t>(address) <= 0x1D5000
			or reinterpret_cast<uintptr_t>(address) > 0x250000)
	{
		size_t index{(address - paging::lowerMemoryLimit) / paging::pageSize};
		_freeFrames.reset(index);
	}
}

void PhysicalMemoryManager::parseMemoryMap()
{
	multiboot::MemoryRegion* region{multiboot::multibootInfoAddress->_mmap_addr};
	const size_t memoryMapSize{multiboot::multibootInfoAddress->_mmap_length};
	Byte* memoryMapUpperBound = reinterpret_cast<Byte*>(region) + memoryMapSize;

	Byte* rawAddress{reinterpret_cast<Byte*>(region)};
	do
	{
		Byte* baseAddress{reinterpret_cast<Byte*>(region->_base_addr)};
		if(region->_type == multiboot::MemoryRegion::_validType
				// Avoid to use the first megabyte
				and baseAddress >= paging::lowerMemoryLimit)
			freeMemoryRegion(*region);

		rawAddress += region->_size + sizeof(region->_size);
		region = reinterpret_cast<multiboot::MemoryRegion*>(rawAddress);

	// While there is yet elements in the map
	} while(rawAddress < memoryMapUpperBound);
}

void PhysicalMemoryManager::freeMemoryRegion(const multiboot::MemoryRegion& region)
{
	// region.base_addr is 64-bits, get only the first 32 bits
	Byte* address{reinterpret_cast<Byte*>(region._base_addr & UINT64_C(0xFFFFFFFF))};
	const size_t size{static_cast<size_t>(region._length)};
	// Get the upper bound aligned to 4k (rounded down to the first 4k multiple)
	Byte * upperBound{alignDown(address + size)};
	address = alignUp(address);

	for(Byte* frame{upperBound - paging::pageSize}; frame >= address; frame -= paging::pageSize)
		// Ensure that the kernel is not added to the free frames
		if(frame + paging::pageSize < reinterpret_cast<Byte*>(&kernelPhysicalStart)
				or frame > reinterpret_cast<Byte*>(&kernelPhysicalEnd))
			freeFrame(frame);
}
