#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstddef>
#include <limits>

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

template <class T>
class Allocator {
	public:
		// type definitions
		typedef T ValueType;
		typedef T* Pointer;
		typedef const T* ConstPointer;
		typedef T& Reference;
		typedef const T& ConstReference;
		typedef size_t SizeType;
		typedef ptrdiff_t DifferenceType;

		template <class U>
		struct Rebind
		{
			typedef Allocator<U> Other;
		};

		Pointer address(Reference value) const
		{
			return &value;
		}

		ConstPointer address(ConstReference value) const
		{
			return &value;
		}

		Allocator()
		{
		}

		Allocator(const Allocator&)
		{
		}

		template <class U>
		Allocator(const Allocator<U>&)
		{
		}

		~Allocator() throw()
		{
		}

		SizeType maxSize() const
		{
			return std::numeric_limits<SizeType>::max() / sizeof(T);
		}

		Pointer allocate(const void* = 0)
		{
			return static_cast<Pointer>(::operator new(sizeof(T)));
		}

		void construct(Pointer pointer, const T& value)
		{
			new(static_cast<void*>(pointer)) T(value);
		}

		void destroy(Pointer pointer)
		{
			pointer->~T();
		}

		void deallocate(Pointer pointer)
		{
			::operator delete(static_cast<void*>(pointer));
		}
};

template <class T1, class T2>
bool operator==(const Allocator<T1>&, const Allocator<T2>&) throw()
{
	return true;
}

template <class T1, class T2>
bool operator!=(const Allocator<T1>&, const Allocator<T2>&) throw()
{
	return false;
}

#endif// MEMORY_HPP
