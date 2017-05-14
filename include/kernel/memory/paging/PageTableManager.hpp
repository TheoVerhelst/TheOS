#ifndef PAGETABLEMANAGER_HPP
#define PAGETABLEMANAGER_HPP

#include <kernel/memory/paging/paging.hpp>
#include <kernel/memory/paging/PhysicalMemoryManager.hpp>

namespace paging
{

class PageTableManager
{
	public:
		/// Constructor.
		PageTableManager();

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

}// namespace paging

#endif // PAGETABLEMANAGER_HPP