#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <boot/MultibootInfo.hpp>
#include <kernel/interrupts/isr.hpp>
#include <kernel/memory/PoolAllocator.hpp>
#include <kernel/memory/MemoryManager.hpp>
#include <kernel/ps2/KeyboardDriver.hpp>

class Kernel final
{
	public:
		/// Maximum number of blocks in the MemoryManager. Even if the memory is
		/// not full, memory allocation will fail if there is too much blocks.
		/// The limit of blocks must be static, and reserve too much room
		/// to blocks information will result in bigger kernel.
		static constexpr size_t _maxBlocksNumber{1 << 16};

		/// The kernel memory allocator type. The complicated template type is a
		/// special static class that will allocate the internal objects needed
		/// by the heap manager, using a pool allocation scheme. So in order to
		/// manage a big heap area, a little pool area is needed, and this is
		/// the template class that will manage this pool area.
		typedef MemoryManager<PoolAllocator<MemoryManager<>::AllocatorValueType, _maxBlocksNumber>> HeapManager;

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
		/// \param info A multiboot info structure that is given by the
		/// bootloader, containing info about the computer and other things.
		void processMultibootInfo(const MultibootInfo& info) const;

		/// Print information about the device on which the kernel was loaded.
		static void printDeviceInfo(uint32_t bootDevice);

		void testHeap();

		void printPrettyAsciiArt();

		/// Size of the heap that will be allocated for the kernel.
		static constexpr size_t _heapSize{1UL << 20UL};

		/// The kernel memory allocator.
		HeapManager _heapManager;

		/// The keyboard driver. It needs to be notified when a keyboard interrupt
		/// occur (with the ISR 33), and it gives a queue of characters that
		/// the user typed.
		ps2::KeyboardDriver _keyboardDriver;
};

/// The main, unique kernel class instance.
extern Kernel kernel;

#endif// KERNEL_HPP
