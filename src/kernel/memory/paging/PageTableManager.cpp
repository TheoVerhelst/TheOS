#include <cpp/flags.hpp>
#include <kernel/memory/paging/bootstrap.hpp>
#include <kernel/memory/paging/PageTableManager.hpp>

namespace paging
{

PageTableManager::PageTableManager():
	_pageDirectory{reinterpret_cast<PageDirectoryEntry*>(bootstrap::kernelPageDirectory)},
	_pageTables{reinterpret_cast<PageTableEntry**>(bootstrap::kernelPageTables)}
{
}

void* PageTableManager::allocatePage()
{
	void* frameAddress{_physicalMemoryManager.allocateFrame()};
	// Iterate over the page directory entries (i.e. over the page tables)
	for(size_t i{0}; i < entriesNumber; ++i)
	{
		// If the page directory is available
		if(flags::allSet(_pageDirectory[i].getFlags(), Flags::Present | Flags::ReadWrite))
		{
			for(size_t j{0}; j < entriesNumber; ++j)
			{
				// If this is a free page
				if(not flags::allSet(_pageTables[i][j].getFlags(), Flags::Present))
				{
					// Set the page table entry to a valid page
					_pageTables[i][j] = PageTableEntry(frameAddress, _defaultFlags);
					return reinterpret_cast<void*>(i * pageTableCoverage + j * pageSize);
				}
			}
		}
	}
	// No suitable page has been found
	return nullptr;
}

} // namespace paging
