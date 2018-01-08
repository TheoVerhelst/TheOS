#include <cpp/flags.hpp>
#include <cpp/log.hpp>
#include <kernel/memory/paging/bootstrap.hpp>
#include <kernel/memory/paging/PageTableManager.hpp>

namespace paging
{

PageTableManager::PageTableManager(const MemoryMap& memoryMap):
	_pageDirectory{reinterpret_cast<PageDirectoryEntry*>(bootstrap::kernelPageDirectory)},
	_physicalMemoryManager{memoryMap}
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
					void* physicalAddress{_physicalMemoryManager.allocateFrame()};
					// Set the page table entry to a valid page
					pageTable[tableEntry] = PageTableEntry(physicalAddress, _defaultFlags);
					void* virtualAddress{reinterpret_cast<void*>((directoryEntry * entriesNumber + tableEntry) * pageSize)};
					invalidatePage(virtualAddress);
					return virtualAddress;
				}
			}
		}
	}

	LOG(Severity::Error) << "No page found for allocation, nullptr returned\n";
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

void PageTableManager::invalidatePage(void* pageAddress)
{
	asm volatile("invlpg (%0)" : : "r" (pageAddress) : "memory");
}

} // namespace paging
