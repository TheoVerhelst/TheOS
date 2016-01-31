#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

#include <stdint.h>
#include <Printer.hpp>
#include <memory.hpp>
#include <boot/MultibootInfo.hpp>

Printer out;

void initMemory(MemoryRegion* address, size_t size)
{
	uintptr_t upperAddress{reinterpret_cast<uintptr_t>(address) + size};
	while(reinterpret_cast<uintptr_t>(address) < upperAddress)
	{
		if(address->type == 1)
		{
			MemoryManager::MemoryBlock* block = MemoryManager::MemoryBlock::allocate();
			block->address = reinterpret_cast<void*>(address->base_addr);
			const size_t index{MemoryManager::getIndexFromSize(static_cast<size_t>(address->length)) - 1};
			block->addToList(MemoryManager::freeBlocks, index);
			out << "Allocated block of size 2^" << index << " starting at " << block->address << "\n";
		}
		address = reinterpret_cast<MemoryRegion*>(reinterpret_cast<uintptr_t>(address) + address->size + sizeof(address->size));
	}
}

void printDeviceInfo(uint32_t boot_device)
{
	const uint32_t drive{boot_device & 0x000000FF};
	out << "Loaded from ";
	switch(drive)
	{
		case 0x00:
			out << "first floppy ";
			break;
		case 0x01:
			out << "second floppy ";
			break;
		case 0x80:
			out << "first hard ";
			break;
		case 0x81:
			out << "second hard ";
			break;
		default:
			out << "unrecogniezed ";
	}
	out << "disk (" << drive << ") on partition ";
	out << ((boot_device & 0x0000FF00) >> 8);
	out << "." << ((boot_device & 0x00FF0000) >> 16);
	out << "." << ((boot_device  & 0xFF000000) >> 24) << "\n";
}

extern "C" void kernel_main(const MultibootInfo& info)
{
	out.setBase(16);
	if(info.flags & InfoAvailable::boot_loader_name)
		out << "This kernel has been loaded by \"" << info.boot_loader_name << "\"\n";
	if(info.flags & InfoAvailable::boot_device)
		printDeviceInfo(info.boot_device);
	if(info.flags & InfoAvailable::mmap)
		initMemory(info.mmap_addr, static_cast<size_t>(info.mmap_length));
}
