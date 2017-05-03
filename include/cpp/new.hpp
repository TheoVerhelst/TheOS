#ifndef NEW_HPP
#define NEW_HPP

#if not __STDC_HOSTED__

[[gnu::__externally_visible__]] void* operator new(size_t size);

[[gnu::__externally_visible__]] void operator delete(void* address);

[[gnu::__externally_visible__]] void operator delete(void* address, size_t size);

[[gnu::__externally_visible__]] void* operator new[](size_t size);

[[gnu::__externally_visible__]] void operator delete[](void* address);

[[gnu::__externally_visible__]] void operator delete[](void* address, size_t size);

[[gnu::__externally_visible__]] inline void* operator new(size_t, void* address)
{
	return address;
}

[[gnu::__externally_visible__]] inline void* operator new[](size_t, void* address)
{
	return address;
}

[[gnu::__externally_visible__]] inline void operator delete(void*, void*)
{
}

[[gnu::__externally_visible__]] inline void operator delete[](void*, void*)
{
}

#endif // not __STDC_HOSTED__

#endif // NEW_HPP
