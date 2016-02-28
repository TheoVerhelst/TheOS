#include <cstdint>
#include <kernel/memory/MemoryMapBrowser.hpp>
#include <Printer.hpp>

MemoryMapBrowser::MemoryMapBrowser():
	_memoryRegions{_memoryRegionsPool}
{
	if(not (multiboot::multibootInfoAddress->_flags & multiboot::InfoAvailable::mmap))
		return;

	multiboot::MemoryRegion* address{multiboot::multibootInfoAddress->_mmap_addr};
	const size_t size{multiboot::multibootInfoAddress->_mmap_length};

	Byte* rawAddress{reinterpret_cast<Byte*>(address)};
	Byte* upperAddress{rawAddress + size};
	while(rawAddress < upperAddress)
	{
		if(address->_type == multiboot::MemoryRegion::_validType)
		{
			MemoryRegion memoryRegion;
			// address->base_addr is 64-bits, get only the first 32 bits
			memoryRegion._address = reinterpret_cast<Byte*>(address->_base_addr & UINT64_C(0xFFFFFFFF));
			memoryRegion._size = static_cast<size_t>(address->_length);
			_memoryRegions.pushBack(memoryRegion);
		}
		rawAddress += address->_size + sizeof(address->_size);
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
