#ifndef NEW_HPP
#define NEW_HPP

#if not __STDC_HOSTED__

void* operator new(size_t size);

void* operator new[](size_t size);

void operator delete(void* address);

void operator delete[](void* address);

void operator delete(void* address, size_t size);

void operator delete[](void* address, size_t size);

#endif // not __STDC_HOSTED__

// In some cases, the placement new appear to be defined, but not declared,
// in hosted environment. So we need to declare outside the condition.
inline void* operator new(size_t size, void* address) noexcept;

inline void* operator new[](size_t size, void* address) noexcept;

inline void operator delete(void* address, void*) noexcept;

inline void operator delete[](void* address, void*) noexcept;

#if not __STDC_HOSTED__

inline void* operator new(size_t, void* address) noexcept
{
	return address;
}

inline void* operator new[](size_t, void* address) noexcept
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
