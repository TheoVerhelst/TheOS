#ifndef PHYSICALMEMORYMANAGER_HPP
#define PHYSICALMEMORYMANAGER_HPP

#include <cstddef>
#include <kernel/memory/Byte.hpp>
#include <kernel/memory/paging.hpp>
#include <boot/MultibootInfo.hpp>
#include <List.hpp>
#include <kernel/memory/PoolAllocator.hpp>

/// \addtogroup Kernel
/// \{

/// Browses the memory map given by the boot loader and manages the physical
/// memory frames with a special stack system.
/// It is final because there can be only one physical memory manager, so
/// inheritance would make no sense.
///
/// The frames are managed as follow: we construct a simply linked list of
/// free frames, where the first word of each free frame is a pointer to the
/// next free frame.
/// We only remember the address of the first free frame (named top of stack),
/// and when a free frame is asked by the kernel, the top of stack is given and
/// the new top of stack is the frame pointed by the old one.
/// When a frame is freed by the kernel, it become the new top of stack, and the
/// address of the old top of stack is written in the first word of the freed
/// frame.
class PhysicalMemoryManager final
{
	public:
		/// Default constructor. It expects multiboot::multibootInfoAddress
		/// to be available for use.
		PhysicalMemoryManager();

		Byte* allocateFrame();
		void freeFrame(Byte* address);

	private:
		/// Parses an element in the memory map, and call itself recursively to
		/// parse the next element. If there is no more element, add it to the
		/// frame stack.
		/// We do a recursive call because we want to copy a buffer of an
		/// unknown size at compile time without heap allocation (because at
		/// this stage there is no heap).
		/// With a recursive call, the data structure is allocated on the stack.
		/// We could use assembly langage to do the same work, but we prefer to
		/// use C++ as much as possible.
		///
		/// \param address The address of the current element in the memory map.
		void parseMemoryMap(multiboot::MemoryRegion* address);

		/// Frees the set of frames contained in the given region.
		/// \param region The region to free.
		void freeMemoryRegion(const multiboot::MemoryRegion& region);

		static constexpr Byte* alignUp(Byte* address);
		static constexpr Byte* alignDown(Byte* address);

		/// The upper limit of the memory map
		Byte* _memoryMapUpperBound;

		/// The top of stack. See main description for more info.
		Byte* _topOfStack;
};

/// A symbol located at the beginning of the kernel image in memory.
/// It is used to retrieve the exact position of the kernel in memory, and its
/// value should not be used. Only its address can be used.
extern "C" void* kernelHighHalfStart;

/// A symbol located at the end of the kernel image in memory.
/// It is used to retrieve the exact position of the kernel in memory, and its
/// value should not be used. Only its address can be used.
extern "C" void* kernelHighHalfEnd;

/// \}

constexpr Byte* PhysicalMemoryManager::alignUp(Byte* address)
{
	const uintptr_t uintAddress{reinterpret_cast<uintptr_t>(address)};
	return reinterpret_cast<Byte*>((uintAddress + paging::pageSize - 1) & ~(paging::pageSize - 1));
}

constexpr Byte* PhysicalMemoryManager::alignDown(Byte* address)
{
	const uintptr_t uintAddress{reinterpret_cast<uintptr_t>(address)};
	return reinterpret_cast<Byte*>(uintAddress & ~(paging::pageSize - 1));
}

#endif// PHYSICALMEMORYMANAGER_HPP
