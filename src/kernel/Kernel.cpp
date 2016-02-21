#include <kernel/gdt.hpp>
#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/pic.hpp>
#include <Printer.hpp>
#include <kernel/Kernel.hpp>

Kernel kernel;

Kernel::Kernel():
	// Give a needed kernel size of zero if multiboot info about memory not available
	// (that's better than nothing)
	_heapManager{multibootInfoAddress->mmap_addr,
			multibootInfoAddress->mmap_length,
			(multibootInfoAddress->flags & InfoAvailable::mmap ? _heapSize : 0UL)}
{
	processMultibootInfo(*multibootInfoAddress);
	gdt::initializeGdt();
	idt::initializeIdt();
	pic::initializePic();
}

void Kernel::run()
{
	abort();
}

MemoryManager& Kernel::getHeapManager()
{
	return _heapManager;
}

void Kernel::abort() const
{
	out << "Aborting...";
	while(true);
}

void Kernel::processMultibootInfo(const MultibootInfo& info) const
{
	if(info.flags & InfoAvailable::boot_loader_name)
		out << "This kernel has been loaded by \"" << info.boot_loader_name << "\"\n";
	if(info.flags & InfoAvailable::boot_device)
		printDeviceInfo(info.boot_device);
	if(not (info.flags & InfoAvailable::mmap))
	{
		out << "Memory map not available, aborting\n";
		abort();
	}
}

void Kernel::printDeviceInfo(uint32_t bootDevice)
{
	const uint32_t drive{bootDevice & 0x000000FF};
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
	out << ((bootDevice & 0x0000FF00) >> 8) << ".";
	out << ((bootDevice & 0x00FF0000) >> 16) << ".";
	out << ((bootDevice & 0xFF000000) >> 24) << "\n";
}
