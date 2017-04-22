#include <cstdint>
#include <kernel/memory/PhysicalMemoryManager.hpp>
#include <kernel/memory/Byte.hpp>
#include <Printer.hpp>

PhysicalMemoryManager::PhysicalMemoryManager():
	_kernelStart{reinterpret_cast<uintptr_t>(&kernelPhysicalStart)},
	_kernelEnd{reinterpret_cast<uintptr_t>(&kernelPhysicalEnd)},
	_lowKernelStart{reinterpret_cast<uintptr_t>(&lowKernelStart)},
	_lowKernelEnd{reinterpret_cast<uintptr_t>(&lowKernelEnd)}
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
		return reinterpret_cast<void*>(paging::lowerMemoryLimit + index * paging::pageSize);
	}
}

void PhysicalMemoryManager::freeFrame(void* address)
{
	intptr_t intAddress{reinterpret_cast<intptr_t>(address)};

	// If the address is not 4k-aligned
	if((intAddress & 0xFFF) != 0)
		return;

	size_t index{(intAddress - paging::lowerMemoryLimit) / paging::pageSize};

	if(index < _freeFrames.size())
		_freeFrames.set(index);
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
		if(region->_type == multiboot::MemoryRegion::_validType
				// Avoid to use the first megabyte
				and region->_base_addr >= paging::lowerMemoryLimit)
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
	out << "address " << region._base_addr << " size " << region._length << "\n";
	// Get the upper bound aligned to 4k (rounded down to the first 4k multiple)
	uintptr_t upperBound{paging::alignDown(address + size)};
	address = paging::alignUp(address);

	for(size_t i{address / paging::pageSize}; i < upperBound / paging::pageSize; ++i)
	{
		const uintptr_t frame{i * paging::pageSize};
		// Ensure that the kernel is not added to the free frames
		if((frame + paging::pageSize < _kernelStart or frame > _kernelEnd)
				// Ensure that the low kernel is not added
				and (frame + paging::pageSize < _lowKernelStart or frame > _lowKernelEnd)
				// Ensure that no low memory is added
				and frame >= paging::lowerMemoryLimit
				// FIXME: If this condition is removed, the boot sequence crashes
				// This may be a special area not told by the BIOS
				and (frame <= 0x1D5000 or frame > 0x250000))
			freeFrame(reinterpret_cast<void*>(frame));
	}
}
