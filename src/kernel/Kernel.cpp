#include <Printer.hpp>
#include <kernel/terminal/Terminal.hpp>
#include <kernel/gdt.hpp>
#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/pic.hpp>
#include <kernel/abort.hpp>
#include <kernel/Kernel.hpp>

Kernel kernel;

Kernel::Kernel():
	// Give a needed kernel size of zero if info about memory is not available
	// (that's better than nothing)
	_heapManager{multibootInfoAddress->mmap_addr,
			multibootInfoAddress->mmap_length,
			(multibootInfoAddress->flags & InfoAvailable::mmap ? _heapSize : 0UL)}
{
	printPrettyAsciiArt();
	processMultibootInfo(*multibootInfoAddress);
	gdt::initializeGdt();
	idt::initializeIdt();
	pic::initializePic();
	testHeap();
}

void Kernel::run()
{
	while(true)
		while(_keyboardDriver.pendingCharacter())
			out << _keyboardDriver.getCharacter();
	abort();
}

Kernel::HeapManager& Kernel::getHeapManager()
{
	return _heapManager;
}

void Kernel::processMultibootInfo(const MultibootInfo& info) const
{
	if(info.flags & InfoAvailable::boot_loader_name)
		out << "This kernel has been loaded by \"" << info.boot_loader_name << "\"\n";
	//if(info.flags & InfoAvailable::boot_device)
	//	printDeviceInfo(info.boot_device);
	if(not (info.flags & InfoAvailable::mmap))
		abort("Memory map not available, aborting\n");
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
			out << "unrecognized ";
	}
	out << "disk (" << drive << ") on partition ";
	out << ((bootDevice & 0x0000FF00) >> 8) << ".";
	out << ((bootDevice & 0x00FF0000) >> 16) << ".";
	out << ((bootDevice & 0xFF000000) >> 24) << "\n";
}

void Kernel::testHeap()
{
	int *ptrA = new int;
	int *ptrB = new int;
	if(ptrA == ptrB)
		out << "Memory allocation failure: allocated 2 int at " << ptrA << ".\n";
	int *oldPtrA = ptrA;
	delete ptrA;
	ptrA = new int;
	if(ptrA != oldPtrA)
		out << "Memory allocation failure: the same object is not reallocated at the same place after deallocation.\n";
	delete ptrB;

	int *ptr8 = new int[8];
	int *ptr2 = new int[2];
	if(ptr8 == ptr2)
		out << "Memory allocation failure: allocated 2 differents objects at " << ptr8 << ".\n";
	int *oldPtr8 = ptr8;
	delete[] ptr8;
	ptr8 = new int;
	if(ptr8 != oldPtr8)
		out << "Memory allocation failure: the same object is not reallocated at the same place after deallocation.\n";
	delete[] ptr2;
}

void Kernel::printPrettyAsciiArt()
{
	terminal.setColourProfile({vga::Colour::Cyan, vga::Colour::Black});
	terminal.putString("\n\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n\
                         \xDC\xDC\xDC\xDC\xDC \xDC         \xDC\xDC\xDC\xDC \xDC\xDC\xDC\xDC\xDC \n\
                           \xDB   \xDB\xDC\xDC   \xDC\xDC\xDC \xDB  \xDB \xDB\n\
                           \xDB   \xDB \xDF\xDB \xDB\xDC\xDC\xDB \xDB  \xDB \xDF\xDF\xDF\xDF\xDB\n\
                           \xDB   \xDB  \xDB \xDF\xDC\xDC\xDC \xDB\xDC\xDC\xDB \xDC\xDC\xDC\xDC\xDB      Stroustrup powered     \n\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n\
");
	terminal.setColourProfile(Terminal::_defaultColourProfile);
}