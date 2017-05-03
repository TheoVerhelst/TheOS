#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <std/cstddef>
#include <std/cstdint>
#include <std/limits>
#include <cpp/utility.hpp>
#include <cpp/new.hpp>

// TODO namespace mem (containing copy and set)

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

template <typename T>
class Allocator
{
	public:
		template <typename... Args>
		T* construct(Args&&... args);

		template <typename... Args>
		void destroy(T* pointer);

		virtual T* allocate();

		virtual void deallocate(T* pointer);

		/// Returns a default instance of Allocator<T>. This may be useful for
		/// classes that takes an allocator but still want to fall back to the
		/// default one in their default constructor.
		static Allocator& getDefault();

	private:
		static Allocator _defaultInstance;
};

template <typename T>
Allocator<T> Allocator<T>::_defaultInstance;

template <typename T>
template <typename... Args>
T* Allocator<T>::construct(Args&&... args)
{
	return ::new (allocate()) T(forward<Args>(args)...);
}

template <typename T>
template <typename... Args>
void Allocator<T>::destroy(T* pointer)
{
	pointer->~T();
	deallocate(pointer);
}

template <typename T>
T* Allocator<T>::allocate()
{
	return static_cast<T*>(::operator new(sizeof(T)));
}

template <typename T>
void Allocator<T>::deallocate(T* pointer)
{
	::operator delete(static_cast<void*>(pointer));
}

template <typename T>
Allocator<T>& Allocator<T>::getDefault()
{
	return _defaultInstance;
}

#endif// MEMORY_HPP
