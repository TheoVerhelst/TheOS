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
		PageDirectoryEntry* _pageDirectory;
		PageTableEntry** _pageTables;
		PhysicalMemoryManager _physicalMemoryManager;
		static constexpr uint16_t _defaultFlags{Flags::Present | Flags::ReadWrite};
};

}// namespace paging

#endif // PAGETABLEMANAGER_HPP
