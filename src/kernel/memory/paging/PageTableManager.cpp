#include <cpp/flags.hpp>
#include <kernel/memory/paging/bootstrap.hpp>
#include <kernel/memory/paging/PageTableManager.hpp>

namespace paging
{

PageTableManager::PageTableManager():
	_pageDirectory{reinterpret_cast<PageDirectoryEntry*>(bootstrap::kernelPageDirectory)}
{
	allocateAlreadyPagedFrames();
}

void* PageTableManager::allocatePage()
{
	for(size_t directoryEntry{0}; directoryEntry < entriesNumber; ++directoryEntry)
	{
		// If the page directory entry is available
		if(flags::allSet(_pageDirectory[directoryEntry].getFlags(), Flags::Present | Flags::ReadWrite))
		{
			PageTableEntry* pageTable{_pageDirectory[directoryEntry].getPageTableAddress()};
			for(size_t tableEntry{0}; tableEntry < entriesNumber; ++tableEntry)
			{
				// If this is a free page
				if(not flags::allSet(pageTable[tableEntry].getFlags(), Flags::Present))
				{
					void* frameAddress{_physicalMemoryManager.allocateFrame()};
					// Set the page table entry to a valid page
					pageTable[tableEntry] = PageTableEntry(frameAddress, _defaultFlags);
					return reinterpret_cast<void*>((directoryEntry * entriesNumber + tableEntry) * pageSize);
				}
			}
		}
	}
	// No suitable page has been found
	return nullptr;
}

void PageTableManager::allocateAlreadyPagedFrames()
{
	for(size_t directoryEntry{0}; directoryEntry < entriesNumber; ++directoryEntry)
	{
		// If the page directory entry is available
		if(flags::allSet(_pageDirectory[directoryEntry].getFlags(), Flags::Present))
		{
			PageTableEntry* pageTable{_pageDirectory[directoryEntry].getPageTableAddress()};
			for(size_t tableEntry{0}; tableEntry < entriesNumber; ++tableEntry)
			{
				// If this is not a free page
				if(flags::allSet(pageTable[tableEntry].getFlags(), Flags::Present))
					_physicalMemoryManager.allocateFrame(pageTable[tableEntry].getFrameAddress());
			}
		}
	}
}

} // namespace paging
