#if not __STDC_HOSTED__

#include <kernel/Kernel.hpp>
#include <cpp/new.hpp>

[[gnu::__externally_visible__]] void* operator new(size_t size)
{
	return Kernel::getInstance().getHeapManager().allocate(size);
}

[[gnu::__externally_visible__]] void operator delete(void* address)
{
	Kernel::getInstance().getHeapManager().deallocate(address);
}

[[gnu::__externally_visible__]] void operator delete(void* address, size_t size)
{
	Kernel::getInstance().getHeapManager().deallocate(address, size);
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
