#ifndef POOLALLOCATOR_HPP
#define POOLALLOCATOR_HPP

#include <std/cstddef>
#include <cpp/BitSet.hpp>
#include <cpp/allocators/Allocator.hpp>
#include <kernel/memory/Byte.hpp>

/// Manage a pool of memory that has a size of sizeof(T) * Size.
template <typename T, size_t Size>
class Pool
{
	public:
		Pool() = default;

		Pool(const Pool&) = delete;

		Pool& operator=(const Pool&) = delete;

		T* allocate();

		void deallocate(T* pointer);

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
class PoolAllocator : public Allocator<T>
{
	public:
		typedef Pool<T, Size> PoolType;

		PoolAllocator(PoolType& pool);

		virtual T* allocate() override;

		virtual void deallocate(T* pointer) override;

	private:
		PoolType& _pool;
};

template <typename T, size_t Size>
T* Pool<T, Size>::allocate()
{
	const size_t blockIndex{_usedBlocks.find(false)};
	if(blockIndex == _usedBlocks._invalidIndex)
		return nullptr;
	_usedBlocks.set(blockIndex);
	return reinterpret_cast<T*>(&_array[blockIndex * _blockSize]);
}

template <typename T, size_t Size>
void Pool<T, Size>::deallocate(T* pointer)
{
	const size_t blockIndex{static_cast<size_t>(pointer - reinterpret_cast<T*>(_array))};
	if(blockIndex < Size)
		_usedBlocks.reset(blockIndex);
}

template <typename T, size_t Size>
PoolAllocator<T, Size>::PoolAllocator(PoolType& pool):
	_pool{pool}
{
}

template <typename T, size_t Size>
T* PoolAllocator<T, Size>::allocate()
{
	return _pool.allocate();
}

template <typename T, size_t Size>
void PoolAllocator<T, Size>::deallocate(T* pointer)
{
	_pool.deallocate(pointer);
}



#endif // POOLALLOCATOR_HPP
