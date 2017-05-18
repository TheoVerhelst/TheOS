#include <cpp/Printer.hpp>
#include <cpp/new.hpp>
#include <kernel/terminal/KernelTerminal.hpp>
#include <kernel/gdt.hpp>
#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/pic.hpp>
#include <cpp/abort.hpp>
#include <kernel/Kernel.hpp>

KernelTerminal kernelTerminal;
Printer out{kernelTerminal};
Kernel* Kernel::_instance{nullptr};

Kernel::Kernel():
	_heapAddress{_pageTableManager.allocatePage()},
	_heapManagerPoolAllocator{_heapManagerPool},
	// Give a needed kernel size of zero if info about memory is not available
	// (that's better than nothing)
	_heapManager{_heapAddress, _heapAddress == nullptr ? 0UL : _heapSize,
	             _heapManagerPoolAllocator}
{
	_instance = this;
	printPrettyAsciiArt();
	processMultibootInfo();
	gdt::initializeGdt();
	idt::initializeIdt();
	pic::initializePic();
}

void Kernel::run()
{
	while(true)
		while(_keyboardDriver.pendingCharacter())
			out << _keyboardDriver.getCharacter();
	abort();
}

Kernel& Kernel::getInstance()
{
	return *_instance;
}

MemoryManager& Kernel::getHeapManager()
{
	return _heapManager;
}

void Kernel::processMultibootInfo() const
{
	const multiboot::MultibootInfo& info{*multiboot::multibootInfoAddress};
	if(info._flags & multiboot::InfoAvailable::boot_loader_name)
		out << "This kernel has been loaded by \"" << info._boot_loader_name << "\"\n";
	if(info._flags & multiboot::InfoAvailable::boot_device)
		printDeviceInfo(info._boot_device);
	if(not (info._flags & multiboot::InfoAvailable::mmap))
		abort("Memory map not available, aborting\n");
}

void Kernel::printDeviceInfo(uint32_t bootDevice)
{
	const uint32_t drive{bootDevice & 0x000000FF};
	out << "Loaded from ";
	switch(drive)
	{
		case 0x00:
			out << "first floppy";
			break;
		case 0x01:
			out << "second floppy";
			break;
		case 0x80:
			out << "first hard";
			break;
		case 0x81:
			out << "second hard";
			break;
		default:
			out << "unrecognized";
	}
	out << " disk (" << drive << ") on partition ";
	out << ((bootDevice & 0x0000FF00) >> 8) << ".";
	out << ((bootDevice & 0x00FF0000) >> 16) << ".";
	out << ((bootDevice & 0xFF000000) >> 24) << "\n";
}

void Kernel::printPrettyAsciiArt()
{
	kernelTerminal.setColourProfile({vga::Colour::Cyan, vga::Colour::Black});
	kernelTerminal.putString("\n\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n\
                         \xDC\xDC\xDC\xDC\xDC \xDC         \xDC\xDC\xDC\xDC \xDC\xDC\xDC\xDC\xDC \n\
                           \xDB   \xDB\xDC\xDC   \xDC\xDC\xDC \xDB  \xDB \xDB\n\
                           \xDB   \xDB \xDF\xDB \xDB\xDC\xDC\xDB \xDB  \xDB \xDF\xDF\xDF\xDF\xDB\n\
                           \xDB   \xDB  \xDB \xDF\xDC\xDC\xDC \xDB\xDC\xDC\xDB \xDC\xDC\xDC\xDC\xDB      Stroustrup powered     \n\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n\
");
	kernelTerminal.setColourProfile(KernelTerminal::_defaultColourProfile);
}
