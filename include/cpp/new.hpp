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
inline void* operator new(size_t size, void* address);

inline void* operator new[](size_t size, void* address);

inline void operator delete(void* address, void*);

inline void operator delete[](void* address, void*);

#if not __STDC_HOSTED__

inline void* operator new(size_t, void* address)
{
	return address;
}

inline void* operator new[](size_t, void* address)
{
	return address;
}

inline void operator delete(void*, void*)
{
}

inline void operator delete[](void*, void*)
{
}

#endif // not __STDC_HOSTED__

#endif // NEW_HPP
