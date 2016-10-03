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

alignas(pageSize) [[gnu::section(".pagingTables")]] uint32_t lowerMemoryPageTable[entriesNumber];

alignas(pageSize) [[gnu::section(".pagingTables")]] uint32_t higherHalfPageTables[higherHalfPageTablesNumber][entriesNumber];


extern "C" [[gnu::section(".init")]] void initKernelPaging()
{
	initLowerMemory();
	initHigherHalf();
}

[[gnu::section(".init")]] void initLowerMemory()
{
	FILL_ENTRY(kernelPageDirectory[0], lowerMemoryPageTable, Flags::Present | Flags::ReadWrite);
	// For each page in the lower memory
	for(size_t i{0}; reinterpret_cast<Byte*>(i * pageSize) < lowerMemoryLimit; ++i)
		FILL_ENTRY(lowerMemoryPageTable[i], i * pageSize, Flags::Present | Flags::ReadWrite);
}

[[gnu::section(".init")]] void initHigherHalf()
{
	// Difference of indexes between a page table in the page tables array
	// and the matching entry in the page directory
	const size_t offset{kernelVirtualOffset / (entriesNumber*pageSize)};

	// For each page table of the higher half
	for(size_t i{0}; i < higherHalfPageTablesNumber; ++i)
	{
		FILL_ENTRY(kernelPageDirectory[i + offset], higherHalfPageTables[i], Flags::Present | Flags::ReadWrite);
		// For each page of this page table
		for(size_t j{0}; j < entriesNumber; ++j)
			FILL_ENTRY(higherHalfPageTables[i][j], (i * entriesNumber * pageSize) + (j * pageSize), Flags::Present | Flags::ReadWrite);
	}
}

}// namespace bootstrap

}// namespace paging
