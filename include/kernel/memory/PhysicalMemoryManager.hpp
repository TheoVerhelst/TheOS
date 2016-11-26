#ifndef PHYSICALMEMORYMANAGER_HPP
#define PHYSICALMEMORYMANAGER_HPP

#include <cstddef>
#include <kernel/memory/Byte.hpp>
#include <kernel/memory/paging.hpp>
#include <boot/MultibootInfo.hpp>
#include <BitSet.hpp>

/// \addtogroup Kernel
/// \{

/// Browses the memory map given by the boot loader and manages the physical
/// memory frames.
/// It is final because there can be only one physical memory manager, so
/// inheritance would make no sense.
///
/// The frames are managed with a bitmap, where each bit represent an usable
/// frame of memory.
class PhysicalMemoryManager final
{
	public:
		/// Default constructor. It expects multiboot::multibootInfoAddress
		/// to be available for use.
		PhysicalMemoryManager();

		/// Allocate a frame and return its address.
		/// \return the address of the allocated frame.
		Byte* allocateFrame();

		/// Free a previously allocated frame.
		/// \param the address of the frame to free.
		void freeFrame(Byte* address);

	private:
		/// Parses the memory map info structure and creates a bitmap of the
		/// available memory.
		void parseMemoryMap();

		/// Frees the set of frames contained in the given region.
		/// \param region The region to free.
		void freeMemoryRegion(const multiboot::MemoryRegion& region);

		BitSet<-static_cast<size_t>(paging::lowerMemoryLimit) / paging::pageSize> _freeFrames;
};

/// Symbols located at precise places in the kernel image, allowing to retrieve
/// the position and size of the kernel in memory.
extern "C" void* kernelVirtualStart;
extern "C" void* kernelVirtualEnd;
extern "C" void* kernelPhysicalStart;
extern "C" void* kernelPhysicalEnd;

/// \}

#endif// PHYSICALMEMORYMANAGER_HPP
