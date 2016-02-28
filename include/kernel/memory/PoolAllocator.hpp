#ifndef POOLALLOCATOR_HPP
#define POOLALLOCATOR_HPP

#include <cstddef>
#include <BitSet.hpp>
#include <kernel/memory/Byte.hpp>

/// Manage a pool of memory that has a size of sizeof(T) * Size.
template <typename T, size_t Size>
class Pool
{
	public:
		typedef T* Pointer;

		Pool() = default;

		Pool(const Pool&) = delete;

		Pool& operator=(const Pool&) = delete;

		Pointer allocate();

		void deallocate(Pointer pointer);

	private:
		static constexpr size_t _blockSize{sizeof(T)};

		/// Indicates in _blocksArray wich blocks are currently used.
		BitSet<Size> _usedBlocks;

		Byte _array[Size * _blockSize];
};

/// Class that dynamically manages a pool of blocks of size sizeof(T),
/// with a maximum number of blocks equal to Size.
/// This class is in facts just a reference wrapper around a Pool instance,
/// and an object of type PoolAllocator have to be bound to an instance of
/// Pool, by the reference argument of the constructor.
template <typename T, size_t Size>
class PoolAllocator
{
	public:
		typedef T ValueType;
		typedef T* Pointer;
		typedef const T* ConstPointer;
		typedef T& Reference;
		typedef const T& ConstReference;
		typedef size_t SizeType;
		typedef ptrdiff_t DifferenceType;
		typedef Pool<T, Size> PoolType;

		template <class U, size_t OtherSize>
		struct Rebind
		{
			typedef PoolAllocator<U, OtherSize> Other;
		};

		PoolAllocator(Pool<T, Size>& pool);

		Pointer allocate();

		void deallocate(Pointer pointer);

	private:
		Pool<T, Size>& _pool;
};

template <typename T, size_t Size>
typename Pool<T, Size>::Pointer Pool<T, Size>::allocate()
{
	const size_t blockIndex{_usedBlocks.find(false)};
	if(blockIndex == ~0UL)
		return nullptr;
	_usedBlocks.set(blockIndex);
	return reinterpret_cast<Pointer>(&_array[blockIndex * _blockSize]);
}

template <typename T, size_t Size>
void Pool<T, Size>::deallocate(Pointer pointer)
{
	const size_t blockIndex{static_cast<size_t>(pointer - reinterpret_cast<Pointer>(_array))};
	if(blockIndex < Size)
		_usedBlocks.reset(blockIndex);
}

template <typename T, size_t Size>
PoolAllocator<T, Size>::PoolAllocator(Pool<T, Size>& pool):
	_pool{pool}
{
}

template <typename T, size_t Size>
typename PoolAllocator<T, Size>::Pointer PoolAllocator<T, Size>::allocate()
{
	return _pool.allocate();
}

template <typename T, size_t Size>
void PoolAllocator<T, Size>::deallocate(Pointer pointer)
{
	_pool.deallocate(pointer);
}

#endif// POOLALLOCATOR_HPP
