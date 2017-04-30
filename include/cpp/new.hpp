#ifndef NEW_HPP
#define NEW_HPP

#if not __STDC_HOSTED__

[[gnu::__externally_visible__]] void* operator new(size_t size) throw();

[[gnu::__externally_visible__]] void operator delete(void* address) throw();

[[gnu::__externally_visible__]] void operator delete(void* address, size_t size) throw();

[[gnu::__externally_visible__]] void* operator new[](size_t size) throw();

[[gnu::__externally_visible__]] void operator delete[](void* address) throw();

[[gnu::__externally_visible__]] void operator delete[](void* address, size_t size) throw();

inline void* operator new(size_t, void* address) noexcept
{
	return address;
}

inline void* operator new[](size_t, void* address)  noexcept
{
	return address;
}

inline void operator delete(void*, void*) noexcept
{
}

inline void operator delete[](void*, void*) noexcept
{
}

#endif // not __STDC_HOSTED__

#endif // NEW_HPP
