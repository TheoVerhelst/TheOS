#include <memory.hpp>
#include <memory/MemoryManager.hpp>
#include <Printer.hpp>

extern MemoryManager kernelHeapMamanger;

void* operator new(size_t size) throw()
{
	return kernelHeapMamanger.allocate(size);
}

void operator delete(void* address) throw()
{
	kernelHeapMamanger.deallocate(address);
}

void operator delete(void* address, size_t size) throw()
{
	kernelHeapMamanger.deallocate(address, size);
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

template <class T>
T* Allocator<T>::allocate()
{
	return new T;
}

template <class T>
void Allocator<T>::deallocate(T* pointer)
{
	delete pointer;
}
