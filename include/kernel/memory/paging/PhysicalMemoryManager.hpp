#ifndef PHYSICALMEMORYMANAGER_HPP
#define PHYSICALMEMORYMANAGER_HPP

#include <std/cstddef>
#include <cpp/BitSet.hpp>
#include <boot/MultibootInfo.hpp>
#include <kernel/memory/paging/paging.hpp>

namespace paging
{

/// Browses the memory map given by the boot loader and manages the physical
/// memory frames.
/// It is final because there can be only one physical memory manager, so
/// inheritance would make no sense.
///
/// The frames are managed with a bitmap, where each bit represent an usable
/// frame of memory.
class PhysicalMemoryManager
{
	public:
		/// Default constructor. It expects multiboot::multibootInfoAddress
		/// to be available for use.
		PhysicalMemoryManager();

		/// Allocate a frame and return its address.
		/// \return the address of the allocated frame.
		void* allocateFrame();

		/// Free a previously allocated frame.
		/// \param the address of the frame to free.
		void freeFrame(void* address);

	private:
		/// Parses the memory map info structure and creates a bitmap of the
		/// available memory.
		void parseMemoryMap();

		/// Frees the set of frames contained in the given region.
		/// \param region The region to free.
		void freeMemoryRegion(const multiboot::MemoryRegion& region);

		/// Gets the first 4k-aligned number that is greater or equal to \a address.
		/// \param address The address to convert.
		/// \return The first 4k-aligned number that is greater or equal to \a address.
		static constexpr uintptr_t alignUp(uintptr_t address);

		/// Gets the first 4k-aligned address that is less or equal to \a address.
		/// \param address The address to convert.
		/// \return The first 4k-aligned address that is less or equal to \a address.
		static constexpr uintptr_t alignDown(uintptr_t address);

		BitSet<(-paging::lowerMemoryLimit) / paging::pageSize> _freeFrames;

		/// Kernel bounds in physical memory.
		const uintptr_t _kernelPhysicalStart;
		const uintptr_t _kernelPhysicalEnd;
		const uintptr_t _lowKernelStart;
		const uintptr_t _lowKernelEnd;
};

/// Symbols located at precise places in the kernel image, allowing to retrieve
/// the position and size of the kernel in memory.
extern "C" void* kernelVirtualStart;
extern "C" void* kernelVirtualEnd;
extern "C" void* kernelPhysicalStart;
extern "C" void* kernelPhysicalEnd;
extern "C" void* lowKernelStart;
extern "C" void* lowKernelEnd;

} // namespace paging

namespace paging
{

// We have to define these methods in the header because they are constexpr
constexpr uintptr_t PhysicalMemoryManager::alignUp(uintptr_t address)
{
	return (address + paging::pageSize - 1) & ~(paging::pageSize - 1);
}

constexpr uintptr_t PhysicalMemoryManager::alignDown(uintptr_t address)
{
	return address & ~(paging::pageSize - 1);
}

} // namespace paging

#endif // PHYSICALMEMORYMANAGER_HPP
