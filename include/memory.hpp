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
		T* allocate();
		void deallocate(T* pointer);
};

#endif// MEMORY_HPP
