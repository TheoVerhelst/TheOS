#include <cstdint>
#include <kernel/memory/PhysicalMemoryManager.hpp>
#include <Printer.hpp>

PhysicalMemoryManager::PhysicalMemoryManager():
	_topOfStack{nullptr}
{
	if(not (multiboot::multibootInfoAddress->_flags & multiboot::InfoAvailable::mmap))
		return;

	multiboot::MemoryRegion* address{multiboot::multibootInfoAddress->_mmap_addr};
	const size_t memoryMapSize{multiboot::multibootInfoAddress->_mmap_length};
	_memoryMapUpperBound = reinterpret_cast<Byte*>(address) + memoryMapSize;

	parseMemoryMap(address);
}

Byte* PhysicalMemoryManager::allocateFrame()
{
	if(_topOfStack == nullptr)
		return nullptr;

	Byte* oldTopOfStack{_topOfStack};
	_topOfStack = *(reinterpret_cast<Byte**>(_topOfStack));
	return oldTopOfStack;
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
		*reinterpret_cast<Byte**>(address) = _topOfStack;
		_topOfStack = address;
	}
}

void PhysicalMemoryManager::parseMemoryMap(multiboot::MemoryRegion* address)
{
	// Copy the memory region on the stack
	const multiboot::MemoryRegion region{*address};

	// Skip to the next element in the memory map
	Byte* rawAddress{reinterpret_cast<Byte*>(address)};
	rawAddress += address->_size + sizeof(address->_size);

	// If there is yet elements in the map, parse them recursively
	if(rawAddress < _memoryMapUpperBound)
		parseMemoryMap(reinterpret_cast<multiboot::MemoryRegion*>(rawAddress));

	// The base address of the memory region described by the current map element
	Byte* baseAddress{reinterpret_cast<Byte*>(region._base_addr & UINT64_C(0xFFFFFFFF))};

	// Now we can free the memory, since all regions has been parsed
	if(region._type == multiboot::MemoryRegion::_validType
			// Avoid to use the first megabyte
			and baseAddress >= paging::lowerMemoryLimit)
		freeMemoryRegion(region);

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
		if(frame + paging::pageSize < reinterpret_cast<Byte*>(&kernelStart)
				or frame > reinterpret_cast<Byte*>(&kernelEnd))
			freeFrame(frame);
}
