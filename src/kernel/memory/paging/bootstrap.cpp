#include <kernel/memory/paging/paging.hpp>
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
	for(size_t i{0UL}; i < entriesNumber; ++i)
	{
		kernelPageDirectory[i] = 0UL;
		for(size_t j{0UL}; j < kernelPageTablesNumber; ++j)
			kernelPageTables[j][i] = 0UL;
	}

	for(size_t i{0}; i < 8; ++i)
	{
		kernelPageDirectory[i] = (reinterpret_cast<intptr_t>(kernelPageTables + i) & 0xFFFFF000) | kernelPagingFlags;
		for(size_t j{0}; j < entriesNumber; ++j)
			kernelPageTables[i][j] = ((i * entriesNumber + j) * pageSize) | kernelPagingFlags;
	}

	for(size_t i{8}; i < 16; ++i)
	{
		kernelPageDirectory[i-8 + (kernelVirtualOffset / pageTableCoverage)] = (reinterpret_cast<intptr_t>(kernelPageTables + i) & 0xFFFFF000) | kernelPagingFlags;
		for(size_t j{0}; j < entriesNumber; ++j)
			kernelPageTables[i][j] = (((i-8) * entriesNumber + j) * pageSize) | kernelPagingFlags;
	}/*

	// map lower memory
	mapMemory(0UL, 16*1024*4096, false);

	// map low kernel
	mapMemory(reinterpret_cast<intptr_t>(&lowKernelStart), reinterpret_cast<intptr_t>(&lowKernelEnd), false);

	// map higher half kernel
	mapMemory(reinterpret_cast<intptr_t>(&kernelPhysicalStart), reinterpret_cast<intptr_t>(&kernelPhysicalEnd), true);
	*/
}

[[gnu::section(".bootInit")]]
void mapMemory(intptr_t start, intptr_t end, bool higherHalf)
{
	// Difference of indexes between a page table in the page tables array
	// and the matching entry in the page directory
	const size_t offset{higherHalf ? kernelVirtualOffset / pageTableCoverage : 0};

	start = BOOTSTRAP_ALIGN_DOWN(start);
	end = BOOTSTRAP_ALIGN_UP(end);

	// Loop over the page directory entries to initialize them
	// i is the index of the current page directory entry
	for(size_t i{start / pageTableCoverage}; i < (end == 0 ? 0 : ((end - 1) / pageTableCoverage) + 1); ++i)
		if(not (kernelPageDirectory[i + offset] & Flags::Present))
			BOOTSTRAP_FILL_ENTRY(kernelPageDirectory[i + offset], &(kernelPageTables[usedPageTables++]), kernelPagingFlags);

	// Loop over the page table entries to initialize them
	// i is the frame number in the whole memory (e.g. when i == 2, we are
	// initializing the frame starting at 0x2000)
	for(size_t i{start / pageSize}; i < (end == 0 ? 0 : ((end - 1) / pageSize) + 1); ++i)
	{
		size_t pageDirectoryIndex{(i / entriesNumber) + offset};
		size_t pageTableIndex{i % entriesNumber};
		if(kernelPageDirectory[pageDirectoryIndex] & Flags::Present)
		{
			uint32_t* pageTable{reinterpret_cast<uint32_t*>(kernelPageDirectory[pageDirectoryIndex] & 0xFFFFF000)};
			BOOTSTRAP_FILL_ENTRY(pageTable[pageTableIndex], i * pageSize, kernelPagingFlags);
		}
	}
}

} // namespace bootstrap

} // namespace paging
