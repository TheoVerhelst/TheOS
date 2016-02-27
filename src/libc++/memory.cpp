#include <memory.hpp>
#include <kernel/Kernel.hpp>
#include <Printer.hpp>

void* operator new(size_t size) throw()
{
	return static_cast<void*>(kernel.getHeapManager().allocate(size));
}

void operator delete(void* address) throw()
{
	kernel.getHeapManager().deallocate(static_cast<Byte*>(address));
}

void operator delete(void* address, size_t size) throw()
{
	kernel.getHeapManager().deallocate(static_cast<Byte*>(address), size);
}

void* operator new[](size_t size) throw()
{
	return operator new(size);
}

void operator delete[](void* address) throw()
{
	operator delete(address);
}

void operator delete[](void* address, size_t size) throw()
{
	operator delete(address, size);
}
