#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <boot/MultibootInfo.hpp>
#include <kernel/interrupts/isr.hpp>
#include <kernel/memory/MemoryManager.hpp>
#include <kernel/ps2/KeyboardDriver.hpp>

class Kernel final
{
	public:
		/// Constructor.
		Kernel();

		/// Main function.
		[[noreturn]] void run();

		MemoryManager& getHeapManager();

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

		static constexpr size_t _heapSize{1UL << 20UL};
		MemoryManager _heapManager;
		ps2::KeyboardDriver _keyboardDriver;
};

/// The main, unique kernel class instance.
extern Kernel kernel;

#endif// KERNEL_HPP
