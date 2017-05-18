#if not __STDC_HOSTED__

#ifndef NEW_HPP
#define NEW_HPP

[[gnu::__externally_visible__]] void* operator new(size_t size);

[[gnu::__externally_visible__]] void* operator new[](size_t size);

[[gnu::__externally_visible__]] void operator delete(void* address);

[[gnu::__externally_visible__]] void operator delete[](void* address);

[[gnu::__externally_visible__]] void operator delete(void* address, size_t size);

[[gnu::__externally_visible__]] void operator delete[](void* address, size_t size);

[[gnu::__externally_visible__]] inline void* operator new(size_t size, void* address);

[[gnu::__externally_visible__]] inline void* operator new[](size_t size, void* address);

[[gnu::__externally_visible__]] inline void operator delete(void* address, void*);

[[gnu::__externally_visible__]] inline void operator delete[](void* address, void*);

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

#endif // NEW_HPP

#endif // not __STDC_HOSTED__
