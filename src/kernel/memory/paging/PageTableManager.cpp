#include <cpp/flags.hpp>
#include <cpp/log.hpp>
#include <cpp/abort.hpp>
#include <boot/paging.hpp>
#include <kernel/memory/paging/PageTableManager.hpp>

namespace paging
{

PageTableManager::PageTableManager(const MemoryMap& memoryMap):
	_pageDirectory{reinterpret_cast<PageDirectoryEntry*>(::boot::paging::kernelPageDirectory)},
	_physicalMemoryManager{memoryMap}
{
	allocateAlreadyPagedFrames();
}

void* PageTableManager::allocatePage()
{
	for(size_t i{0}; i < entriesNumber; ++i)
	{
		// If the page directory entry is available
		if(flags::allSet(_pageDirectory[i].getFlags(), Flags::Present | Flags::ReadWrite))
		{
			PageTableEntry* pageTable{_pageDirectory[i].getPageTableAddress()};
			for(size_t j{0}; j < entriesNumber; ++j)
			{
				// If this is a free page
				if(not flags::allSet(pageTable[j].getFlags(), Flags::Present))
				{
					void* physicalAddress{_physicalMemoryManager.allocateFrame()};
					if(physicalAddress == nullptr)
						abort("No frame found when allocating a page");

					// Set the page table entry to a valid page
					pageTable[j] = PageTableEntry(physicalAddress, _defaultFlags);
					void* virtualAddress{reinterpret_cast<void*>((i * entriesNumber + j) * pageSize)};
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
	for(size_t i{0}; i < entriesNumber; ++i)
	{
		// If the page directory entry is available
		if(flags::allSet(_pageDirectory[i].getFlags(), Flags::Present))
		{
			PageTableEntry* pageTable{_pageDirectory[i].getPageTableAddress()};
			for(size_t j{0}; j < entriesNumber; ++j)
			{
				// If this is not a free page
				if(flags::allSet(pageTable[j].getFlags(), Flags::Present))
					_physicalMemoryManager.allocateFrame(pageTable[j].getFrameAddress());
			}
		}
	}
}

void PageTableManager::invalidatePage(void* pageAddress)
{
	asm volatile("invlpg (%0)" : : "r" (pageAddress) : "memory");
}

} // namespace paging
