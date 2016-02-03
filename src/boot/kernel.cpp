#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

#include <kernel/kernel.hpp>
#include <memory/GDT.hpp>
#include <Printer.hpp>
#include <boot/MultibootInfo.hpp>

class C
{
	public:
		C()
		{
			out << "C()\n";
		}

		~C()
		{
			out << "~C()\n";
		}
};
class D
{
	public:
		D()
		{
			out << "D()\n";
		}

		~D()
		{
			out << "~D()\n";
		}
		int x;
};

extern "C" void kernel_main(const MultibootInfo& info)
{
	out.setBase(16);
	if(info.flags & InfoAvailable::boot_loader_name)
		out << "This kernel has been loaded by \"" << info.boot_loader_name << "\"\n";
	if(info.flags & InfoAvailable::mmap)
		initKernelHeap(info.mmap_addr, static_cast<size_t>(info.mmap_length));
	initializeGDT();
	//Test heap
	C* c = new C;
	out << "c Address = " << c << "\n";
	delete c;
	D* d = new D;
	out << "d Address = " << d << "\n";
	delete d;
}

void initKernelHeap(MemoryRegion* address, size_t size)
{
	uintptr_t upperAddress{reinterpret_cast<uintptr_t>(address) + size};
	while(reinterpret_cast<uintptr_t>(address) < upperAddress)
	{
		if(address->type == 1 and static_cast<size_t>(address->length) >= kernelHeapSize)
		{
			void* baseAddress{reinterpret_cast<void*>(address->base_addr)};
			kernelHeapMamanger.addMemoryChunk(baseAddress, kernelHeapSize);
			out << "Allocated kernel heap of size " << kernelHeapSize/1000 << " Ko starting at " << baseAddress << "\n";
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
	out << ((boot_device & 0x0000FF00) >> 8) << ".";
	out << ((boot_device & 0x00FF0000) >> 16) << ".";
	out << ((boot_device & 0xFF000000) >> 24) << "\n";
}
