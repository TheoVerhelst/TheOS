#include <cstdint>
#include <kernel/memory/MemoryMapBrowser.hpp>
#include <Printer.hpp>

MemoryMapBrowser::MemoryMapBrowser():
	_memoryRegions{_memoryRegionsPool}
{
	if(not (multiboot::multibootInfoAddress->flags & multiboot::InfoAvailable::mmap))
		return;

	multiboot::MemoryRegion* address{multiboot::multibootInfoAddress->mmap_addr};
	const size_t size{multiboot::multibootInfoAddress->mmap_length};

	Byte* rawAddress{reinterpret_cast<Byte*>(address)};
	Byte* upperAddress{rawAddress + size};
	while(rawAddress < upperAddress)
	{
		if(address->type == multiboot::MemoryRegion::validType)
		{
			MemoryRegion memoryRegion;
			// address->base_addr is 64-bits, get only the first 32 bits
			memoryRegion._address = reinterpret_cast<Byte*>(address->base_addr & UINT64_C(0xFFFFFFFF));
			memoryRegion._size = static_cast<size_t>(address->length);
			_memoryRegions.pushBack(memoryRegion);
		}
		rawAddress += address->size + sizeof(address->size);
		address = reinterpret_cast<multiboot::MemoryRegion*>(rawAddress);
	}
}

Byte* MemoryMapBrowser::findMemoryRegion(size_t neededRegionSize)
{
	for(auto it(_memoryRegions.begin()); it != _memoryRegions.end(); ++it)
	{
		if(it->_size >= neededRegionSize)
		{
			Byte* res{it->_address};
			// Avoid giving nullptr as result
			if(res == nullptr and neededRegionSize > 0)
				res++;
			it->_address += neededRegionSize;
			it->_size -= neededRegionSize;
			if(it->_size == 0)
				_memoryRegions.erase(it);
			return res;
		}
	}
	return nullptr;
}
