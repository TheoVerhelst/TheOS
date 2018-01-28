#include <cpp/Printer.hpp>
#include <cpp/new.hpp>
#include <cpp/abort.hpp>
#include <kernel/Kernel.hpp>

Kernel* Kernel::_instance{nullptr};

Kernel::Kernel(const multiboot::MemoryMap& memoryMap, AbstractKeyboardDriver& keyboardDriver):
	_pageTableManager{memoryMap},
	_heapAddress{_pageTableManager.allocatePage()},
	_heapManagerPoolAllocator{_heapManagerPool},
	// Give a needed kernel size of zero if info about memory is not available
	// (that's better than nothing)
	_heapManager{_heapAddress, _heapAddress == nullptr ? 0UL : _heapSize,
	             _heapManagerPoolAllocator},
	_keyboardDriver{keyboardDriver}
{
	_instance = this;
	printPrettyAsciiArt();
}

void Kernel::run()
{
	while(true)
		while(not _keyboardDriver.characterQueueEmpty())
			out << _keyboardDriver.getCharacter();
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
	out << "\
\n\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\
\n\
                         \xDC\xDC\xDC\xDC\xDC \xDC         \xDC\xDC\xDC\xDC \xDC\xDC\xDC\xDC\xDC \n\
                           \xDB   \xDB\xDC\xDC   \xDC\xDC\xDC \xDB  \xDB \xDB\n\
                           \xDB   \xDB \xDF\xDB \xDB\xDC\xDC\xDB \xDB  \xDB \xDF\xDF\xDF\xDF\xDB\n\
                           \xDB   \xDB  \xDB \xDF\xDC\xDC\xDC \xDB\xDC\xDC\xDB \xDC\xDC\xDC\xDC\xDB      Stroustrup powered\
\n\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\
\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\
\n\
";
}
