#ifndef PAGETABLEMANAGER_HPP
#define PAGETABLEMANAGER_HPP

#include <kernel/multiboot/MemoryMap.hpp>
#include <kernel/arch/i386/memory/paging/paging.hpp>
#include <kernel/arch/i386/memory/paging/PhysicalMemoryManager.hpp>

namespace paging
{

class PageTableManager
{
	public:
		/// Constructor.
		/// \param memoryMap The memory map containing all available memory
		/// areas, constructed from the multiboot info.
		PageTableManager(const multiboot::MemoryMap& memoryMap);

		void* allocatePage();

	private:
		void allocateAlreadyPagedFrames();

		/// Invalidates a page in the TLB (table lookaside buffer) from its
		/// virtual address. This function should be called each time a page
		/// table entry is modified.
		/// \param pageAddress The virtual address of the page to invalidate.
		static void invalidatePage(void* pageAddress);

		PageDirectoryEntry* _pageDirectory;
		PhysicalMemoryManager _physicalMemoryManager;
		static constexpr uint16_t _defaultFlags{Flags::Present | Flags::ReadWrite};
};

} // namespace paging

#endif // PAGETABLEMANAGER_HPP
