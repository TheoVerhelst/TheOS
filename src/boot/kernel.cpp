#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

#include <kernel/kernel.hpp>
#include <kernel/GDT.hpp>
#include <Printer.hpp>
#include <boot/MultibootInfo.hpp>

extern "C" void kernel_main(const MultibootInfo& info)
{
	if(info.flags & InfoAvailable::boot_loader_name)
		out << "This kernel has been loaded by \"" << info.boot_loader_name << "\"\n";
	if(info.flags & InfoAvailable::boot_device)
		printDeviceInfo(info.boot_device);
	if(info.flags & InfoAvailable::mmap)
		initKernelHeap(info.mmap_addr, info.mmap_length);
	else
	{
		out << "Memory map not available, aborting\n";
		return;
	}
	initializeGDT();
	out.setShowPrefix(false);
}

void initKernelHeap(MemoryRegion* address, size_t size)
{
	uintptr_t rawAddress{reinterpret_cast<uintptr_t>(address)};
	const uintptr_t upperAddress{rawAddress + size};
	while(rawAddress < upperAddress)
	{
		if(address->type == 1 and static_cast<size_t>(address->length) >= kernelHeapSize)
		{
			void* baseAddress{reinterpret_cast<void*>(address->base_addr)};
			kernelHeapMamanger.addMemoryChunk(baseAddress, kernelHeapSize);
			out << "Allocated kernel heap of size " << kernelHeapSize/1000 << " Ko starting at " << baseAddress << "\n";
			break;
		}
		rawAddress += address->size + sizeof(address->size);
		address = reinterpret_cast<MemoryRegion*>(rawAddress);
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
	out << ((boot_device & 0x0000FF00) >> 8) << ".";
	out << ((boot_device & 0x00FF0000) >> 16) << ".";
	out << ((boot_device & 0xFF000000) >> 24) << "\n";
}
