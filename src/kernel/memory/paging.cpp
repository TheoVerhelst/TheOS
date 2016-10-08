#include <kernel/memory/paging.hpp>

namespace paging
{

PageTableEntry::PageTableEntry(Byte* physicalAddress, uint16_t flags)
{
	set(physicalAddress, flags);
}

void PageTableEntry::set(Byte* physicalAddress, uint16_t flags)
{
	_physicalAddress = reinterpret_cast<uint32_t>(physicalAddress) >> 12;
	_flags = flags;
}

PageDirectoryEntry::PageDirectoryEntry(PageTableEntry* pageTable, uint16_t flags)
{
	set(pageTable, flags);
}

void PageDirectoryEntry::set(PageTableEntry* pageTable, uint16_t flags)
{
	_pageTable = reinterpret_cast<uint32_t>(pageTable) >> 12;
	_flags = flags;
}

namespace bootstrap
{

alignas(pageSize) [[gnu::section(".pagingTables")]] uint32_t kernelPageDirectory[entriesNumber];

alignas(pageSize) [[gnu::section(".pagingTables")]] uint32_t kernelPageTables[kernelPageTablesNumber][entriesNumber];

size_t usedPageTables{0UL};

extern "C" [[gnu::section(".bootInit")]] void initKernelPaging()
{
	for(size_t i{0UL}; i < entriesNumber; ++i)
	{
		kernelPageDirectory[i] = 0UL;
		for(size_t j{0UL}; j < kernelPageTablesNumber; ++j)
			kernelPageTables[j][i] = 0UL;
	}
	// map lower memory
	mapMemory(reinterpret_cast<Byte*>(0), lowerMemoryLimit, false);

	// map low kernel
	mapMemory(reinterpret_cast<Byte*>(&lowKernelStart), reinterpret_cast<Byte*>(&lowKernelEnd), false);

	// map higher half kernel
	//mapMemory(reinterpret_cast<Byte*>(&kernelPhysicalStart), reinterpret_cast<Byte*>(&kernelPhysicalEnd), true);
}

[[gnu::section(".bootInit")]] void mapMemory(Byte* start, Byte* end, bool higherHalf)
{
	// Difference of indexes between an identity paging and a higher half paging
	// in the page directory
	const size_t offset{higherHalf ? kernelVirtualOffset / pageTableCoverage : 0};

	const size_t castedStart{reinterpret_cast<uintptr_t>(BOOTSTRAP_ALIGN_DOWN(start))};
	const size_t castedEnd{reinterpret_cast<uintptr_t>(BOOTSTRAP_ALIGN_UP(end))};

	// Loop over the page directory entries to initialize them
	// i is the index of the current page directory entry
	for(size_t i{castedStart / pageTableCoverage}; i < castedEnd / pageTableCoverage; ++i)
	{
		if(not (kernelPageDirectory[i + offset] & Flags::Present))
			BOOTSTRAP_FILL_ENTRY(kernelPageDirectory[i + offset], &(kernelPageTables[usedPageTables++]), kernelPagingFlags);
	}

	// Loop over the page table entries to initialize them
	// i is the frame number in the whole memory (e.g. when i == 2, we are
	// initializing the frame starting at 0x2000)
	for(size_t i{castedStart / pageSize}; i < castedEnd / pageSize; ++i)
	{
		size_t pageDirectoryIndex{(i / entriesNumber) + offset};
		size_t pageTableIndex{i % entriesNumber};
		uint32_t* pageTable{reinterpret_cast<uint32_t*>(kernelPageDirectory[pageDirectoryIndex] & 0xFFFFF000)};
		BOOTSTRAP_FILL_ENTRY(pageTable[pageTableIndex], i * pageSize, kernelPagingFlags);
	}
}

}// namespace bootstrap

}// namespace paging
