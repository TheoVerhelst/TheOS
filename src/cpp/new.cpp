#if not __STDC_HOSTED__

#include <std/cstddef>
#include <cpp/new.hpp>
#include <kernel/Kernel.hpp>

void* operator new(size_t size)
{
	// Allocate with kernel heap manager, and request an alignment at least
	// as big as std::max_align_t's one, as requested by the standard.
	return Kernel::getInstance().getHeapManager().allocate(size, alignof(std::max_align_t));
}

void* operator new[](size_t size)
{
	return operator new(size);
}

void operator delete(void* address)
{
	if(address != nullptr)
		Kernel::getInstance().getHeapManager().deallocate(address);
}

void operator delete[](void* address)
{
	operator delete(address);
}

void operator delete(void* address, size_t)
{
	operator delete(address);
}

void operator delete[](void* address, size_t)
{
	operator delete(address);
}

#endif // not __STDC_HOSTED__
