#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cpp/utility.hpp>
#include <cpp/new.hpp>

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
	return new (static_cast<void*>(allocate())) T(forward<Args>(args)...);
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
	operator delete(static_cast<void*>(pointer));
}

template <typename T>
Allocator<T>& Allocator<T>::getDefault()
{
	return _defaultInstance;
}

#endif // ALLOCATOR_HPP
