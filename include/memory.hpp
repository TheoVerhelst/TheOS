#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstddef>

void* operator new(size_t size) throw()
	__attribute__((__externally_visible__));
void operator delete(void* address) throw()
	__attribute__((__externally_visible__));
void operator delete(void* address, size_t size) throw()
	__attribute__((__externally_visible__));
void* operator new[](size_t size) throw()
	__attribute__((__externally_visible__));
void operator delete[](void* address) throw()
	__attribute__((__externally_visible__));
void operator delete[](void* address, size_t size) throw()
	__attribute__((__externally_visible__));

template <class T>
class Allocator
{
	public:
		typedef T ValueType;
		typedef T* Pointer;
		T* allocate();
		void deallocate(T* pointer);
};

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

#endif// MEMORY_HPP
