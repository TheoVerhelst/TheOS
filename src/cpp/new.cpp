#include <kernel/Kernel.hpp>
#include <cpp/new.hpp>

#if not __STDC_HOSTED__

[[gnu::__externally_visible__]] void* operator new(size_t size)
{
	return kernel.getHeapManager().allocate(size);
}

[[gnu::__externally_visible__]] void operator delete(void* address)
{
	kernel.getHeapManager().deallocate(address);
}

[[gnu::__externally_visible__]] void operator delete(void* address, size_t size)
{
	kernel.getHeapManager().deallocate(address, size);
}

[[gnu::__externally_visible__]] void* operator new[](size_t size)
{
	return ::operator new(size);
}

[[gnu::__externally_visible__]] void operator delete[](void* address)
{
	::operator delete(address);
}

[[gnu::__externally_visible__]] void operator delete[](void* address, size_t size)
{
	::operator delete(address, size);
}

#endif // not __STDC_HOSTED__
