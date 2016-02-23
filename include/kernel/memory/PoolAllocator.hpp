#ifndef POOLALLOCATOR_HPP
#define POOLALLOCATOR_HPP

#include <BitSet.hpp>

/// Class that dynamically manages a static pool of blocks of size sizeof(T),
/// with a maximum number of blocks equal to Size.
template <typename T, size_t Size>
class PoolAllocator
{
	public:
		typedef T ValueType;
		typedef T* Pointer;

		Pointer allocate();
		void deallocate(Pointer pointer);

	private:
		static constexpr size_t _blockSize{sizeof(T)};

		/// Indicates in _blocksArray wich blocks are currently used.
		static BitSet<Size> _usedBlocks;

		/// An array of blocks. According to §3.9.2 of the ISO C++14 standard,
		/// it is guaranteed that an array of char is suitable to hold the bytes
		/// of any object of type T.
		static char _blocksArray[Size * _blockSize];
};

template <typename T, size_t Size>
BitSet<Size> PoolAllocator<T, Size>::_usedBlocks;

template <typename T, size_t Size>
char PoolAllocator<T, Size>::_blocksArray[Size * PoolAllocator<T, Size>::_blockSize];

template <typename T, size_t Size>
typename PoolAllocator<T, Size>::Pointer PoolAllocator<T, Size>::allocate()
{
	const size_t blockIndex{_usedBlocks.find(false)};
	if(blockIndex == ~0UL)
		return nullptr;
	_usedBlocks.set(blockIndex);
	return reinterpret_cast<Pointer>(&_blocksArray[blockIndex * _blockSize]);
}

template <typename T, size_t Size>
void PoolAllocator<T, Size>::deallocate(Pointer pointer)
{
	const size_t blockIndex{static_cast<size_t>(reinterpret_cast<char *>(pointer) - _blocksArray) / _blockSize};
	if(blockIndex < Size)
		_usedBlocks.reset(blockIndex);
}

#endif// POOLALLOCATOR_HPP
