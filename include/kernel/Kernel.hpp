#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <boot/MultibootInfo.hpp>
#include <kernel/interrupts/isr.hpp>
#include <kernel/memory/PoolAllocator.hpp>
#include <kernel/memory/MemoryManager.hpp>
#include <kernel/memory/PhysicalMemoryManager.hpp>
#include <kernel/memory/Byte.hpp>
#include <kernel/ps2/KeyboardDriver.hpp>

/// \defgroup Kernel Kernel
/// All classes and functions directly related to the kernel
/// \{

class Kernel final
{
	private:
		/// Size of the heap that will be allocated for the kernel.
		static constexpr size_t _heapSize{paging::pageSize};

	public:
		/// Maximum number of blocks in the MemoryManager. Even if the memory is
		/// not full, memory allocation will fail if there is too much blocks.
		/// The limit of blocks must be static, and reserve too much room
		/// to blocks information will result in bigger kernel.
		/// The value 8 is totally arbitrary.
		static constexpr size_t _maxBlocksNumber{_heapSize / 8};

		/// The type of the allocator that the heap manager will use to allocate
		/// the elements of its internal lists. In order to manage a big heap
		/// area, a little pool area is needed. This is a pool allocator that
		/// uses a pool instance stored as an attribute of the kernel.
		typedef PoolAllocator<MemoryManager<>::AllocatorValueType, _maxBlocksNumber> HeapManagerPoolAllocator;

		/// The kernel heap allocator type.
		typedef MemoryManager<HeapManagerPoolAllocator> HeapManager;

		/// The type of the pool used by the internal allocator of the heap
		/// manager.
		typedef typename HeapManagerPoolAllocator::PoolType HeapManagerPool;

		/// Constructor.
		Kernel();

		/// Main function.
		[[noreturn]] void run();

		HeapManager& getHeapManager();

	private:
		/// The static class isr::Table have access to member of the kernel
		/// (so the ISRs can modify the kernel).
		friend class isr::Table;

		/// Process the information given by the bootloader.
		void processMultibootInfo() const;

		/// Print information about the device on which the kernel was loaded.
		static void printDeviceInfo(uint32_t bootDevice);

		void testHeap();

		void printPrettyAsciiArt();

		PhysicalMemoryManager _physicalMemoryManager;

		Byte* _heapAddress;

		HeapManagerPool _heapManagerPool;

		/// The kernel memory allocator.
		HeapManager _heapManager;

		/// The keyboard driver. It needs to be notified when a keyboard
		/// interrupt occur (with the ISR 33), and it gives a queue of
		/// characters that the user typed.
		ps2::KeyboardDriver _keyboardDriver;
};

/// The main, unique kernel class instance.
extern Kernel kernel;

/// \}

#endif// KERNEL_HPP
