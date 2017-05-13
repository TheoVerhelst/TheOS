#include <kernel/memory/paging/paging.hpp>
#include <kernel/memory/kernelLocation.hpp>
#include <kernel/memory/paging/bootstrap.hpp>

namespace paging
{

namespace bootstrap
{

alignas(pageSize) [[gnu::section(".kernelPaging")]]
uint32_t kernelPageDirectory[entriesNumber];

alignas(pageSize) [[gnu::section(".kernelPaging")]]
uint32_t kernelPageTables[kernelPageTablesNumber][entriesNumber];

size_t usedPageTables{0UL};

extern "C" [[gnu::section(".bootInit")]]
void initKernelPaging()
{
	// Clear all entries to zero
	for(size_t i{0UL}; i < entriesNumber; ++i)
	{
		kernelPageDirectory[i] = 0UL;
		for(size_t j{0UL}; j < kernelPageTablesNumber; ++j)
			kernelPageTables[j][i] = 0UL;
	}

	/*
	for(size_t i{0}; i < 8; ++i)
	{
		kernelPageDirectory[i] = (reinterpret_cast<uint32_t>(&kernelPageTables[i]) & 0xFFFFF000) | kernelPagingFlags;
		for(size_t j{0}; j < entriesNumber; ++j)
			kernelPageTables[i][j] = ((i * entriesNumber + j) * pageSize) | kernelPagingFlags;
	}

	for(size_t i{8}; i < 16; ++i)
	{
		kernelPageDirectory[i-8 + (kernelVirtualOffset / pageTableCoverage)] = (reinterpret_cast<intptr_t>(kernelPageTables + i) & 0xFFFFF000) | kernelPagingFlags;
		for(size_t j{0}; j < entriesNumber; ++j)
			kernelPageTables[i][j] = (((i-8) * entriesNumber + j) * pageSize) | kernelPagingFlags;
	}*/

	// map lower memory
	mapMemory(0UL, lowerMemoryLimit, false);

	// map low kernel
	mapMemory(reinterpret_cast<uintptr_t>(&lowKernelStart), reinterpret_cast<uintptr_t>(&lowKernelEnd), false);

	// map higher half kernel
	mapMemory(reinterpret_cast<uintptr_t>(&kernelPhysicalStart), reinterpret_cast<uintptr_t>(&kernelPhysicalEnd), true);

}

[[gnu::section(".bootInit")]]
void mapMemory(uintptr_t start, uintptr_t end, bool higherHalf)
{
	start = BOOTSTRAP_ALIGN_UP(start);
	end = BOOTSTRAP_ALIGN_DOWN(end);
	const size_t indexOffset{higherHalf ? kernelVirtualOffset / pageTableCoverage : 0};
	const size_t firstDirectoryEntry{start / pageTableCoverage};
	const size_t lastDirectoryEntry{(end - 1) / pageTableCoverage};
	// directoryEntry is the current page directory entry
	for(size_t directoryEntry{firstDirectoryEntry}; directoryEntry <= lastDirectoryEntry; ++directoryEntry)
	{
		// If the page directory entry is not filled yet
		if(not (kernelPageDirectory[directoryEntry + indexOffset] & Flags::Present))
		{
			// Use a new page table from the array
			kernelPageDirectory[directoryEntry + indexOffset] =
					(reinterpret_cast<uint32_t>(&kernelPageTables[usedPageTables]) & 0xFFFFF000) | kernelPagingFlags;
			++usedPageTables;
		}

		uint32_t* pageTable{reinterpret_cast<uint32_t*>(kernelPageDirectory[directoryEntry + indexOffset] & 0xFFFFF000)};
		// TODO use start and end rather than maping the whole page table
		// tableEntry is the current page table entry
		for(size_t tableEntry{0}; tableEntry < entriesNumber; ++tableEntry)
			pageTable[tableEntry] = (((directoryEntry * entriesNumber + tableEntry) * pageSize) & 0xFFFFF000) | kernelPagingFlags;
	}
}

} // namespace bootstrap

} // namespace paging
