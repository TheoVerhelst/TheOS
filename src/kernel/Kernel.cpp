#include <cpp/Printer.hpp>
#include <cpp/new.hpp>
#include <kernel/terminal/KernelTerminal.hpp>
#include <cpp/abort.hpp>
#include <kernel/Kernel.hpp>

KernelTerminal kernelTerminal;
Printer out{kernelTerminal};
Kernel* Kernel::_instance{nullptr};

Kernel::Kernel(const MemoryMap& memoryMap):
	_pageTableManager{memoryMap},
	_heapAddress{_pageTableManager.allocatePage()},
	_heapManagerPoolAllocator{_heapManagerPool},
	// Give a needed kernel size of zero if info about memory is not available
	// (that's better than nothing)
	_heapManager{_heapAddress, _heapAddress == nullptr ? 0UL : _heapSize,
	             _heapManagerPoolAllocator}
{
	_instance = this;
	printPrettyAsciiArt();
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
