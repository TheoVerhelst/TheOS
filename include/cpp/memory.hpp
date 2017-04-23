#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstddef>
#include <cstdint>
#include <limits>

/// Copies count characters from the object pointed to by \a src to the object
/// pointed to by \a dest. Both objects are interpreted as arrays of unsigned
/// char.
///
/// The behavior is undefined if access occurs beyond the end of the \a dest
/// array. If the objects overlap, the behavior is undefined. The behavior is
/// undefined if either \a dest or \a src is a null pointer.
/// \param dest Pointer to the object to copy to.
/// \param src Pointer to the object to copy from.
/// \param count Number of bytes to copy.
void memcpy(void* dest, const void* src, size_t count);

/// Copies the value \a value into the memory place pointed to by \a dest.
/// This function is needed as an extern "C" function by GCC since we are in
/// freestanding environment.
/// \param dest Pointer to the object to copy.
/// \param value The value to fill.
/// \param count Number of times to fill.
extern "C" void memset(void* dest, char value, size_t count);

/// Copies the value \a value into the memory place pointed to by \a dest.
///
/// \param dest Pointer to the object to copy.
/// \param value The value to fill.
/// \param count Number of times to fill.
void memset(void* dest, uint16_t value, size_t count);

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
