#include <kernel/Kernel.hpp>
#include <cpp/new.hpp>

#if not __STDC_HOSTED__

void* operator new(size_t size) throw()
{
	return kernel.getHeapManager().allocate(size);
}

void operator delete(void* address) throw()
{
	kernel.getHeapManager().deallocate(static_cast<void*>(address));
}

void operator delete(void* address, size_t size) throw()
{
	kernel.getHeapManager().deallocate(static_cast<void*>(address), size);
}

void* operator new[](size_t size) throw()
{
	return ::operator new(size);
}

void operator delete[](void* address) throw()
{
	::operator delete(address);
}

void operator delete[](void* address, size_t size) throw()
{
	::operator delete(address, size);
}

#endif // not __STDC_HOSTED__
