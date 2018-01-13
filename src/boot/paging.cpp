#include <kernel/memory/paging/paging.hpp>
#include <kernel/memory/kernelLocation.hpp>
#include <boot/gdt.hpp>
#include <boot/paging.hpp>

namespace boot
{

namespace paging
{

alignas(::paging::pageSize) [[gnu::section(".bootBss")]]
uint32_t kernelPageDirectory[::paging::entriesNumber];

alignas(::paging::pageSize) [[gnu::section(".bootBss")]]
uint32_t kernelPageTables[kernelPageTablesNumber][::paging::entriesNumber];

[[gnu::section(".bootBss")]]
size_t usedPageTables;

extern "C" [[gnu::section(".bootText")]]
void initKernelPaging()
{
	gdt::initializeGdt();

	usedPageTables = 0;

	// Clear all entries to zero
	for(size_t i{0UL}; i < ::paging::entriesNumber; ++i)
		kernelPageDirectory[i] = 0UL;

	for(size_t j{0UL}; j < kernelPageTablesNumber; ++j)
		for(size_t i{0UL}; i < ::paging::entriesNumber; ++i)
			kernelPageTables[j][i] = 0UL;

	// map lower memory
	mapMemory(0UL, lowerMemoryLimit, false);

	// map low kernel
	mapMemory(reinterpret_cast<uintptr_t>(&lowKernelStart), reinterpret_cast<uintptr_t>(&lowKernelEnd), false);

	// map higher half kernel
	mapMemory(reinterpret_cast<uintptr_t>(&kernelPhysicalStart), reinterpret_cast<uintptr_t>(&kernelPhysicalEnd), true);
}

[[gnu::section(".bootText")]]
void mapMemory(uintptr_t start, uintptr_t end, bool higherHalf)
{
	start = BOOTSTRAP_ALIGN_DOWN(start);
	end = BOOTSTRAP_ALIGN_UP(end);
	const size_t directoryOffset{higherHalf ? kernelVirtualOffset / ::paging::pageTableCoverage : 0};
	const size_t firstPage{start / ::paging::pageSize};
	const size_t pastLastPage{end / ::paging::pageSize};

	for(size_t page{firstPage}; page < pastLastPage; ++page)
	{
		const size_t directoryEntry{(page / ::paging::entriesNumber) + directoryOffset};
		if(not (kernelPageDirectory[directoryEntry] & ::paging::Flags::Present))
		{
			// Use a new page table from the array
			BOOTSTRAP_FILL_ENTRY(kernelPageDirectory[directoryEntry],
				&kernelPageTables[usedPageTables], kernelPagingFlags);
			++usedPageTables;
		}

		uint32_t* pageTable{reinterpret_cast<uint32_t*>(kernelPageDirectory[directoryEntry] & 0xFFFFF000)};
		const size_t tableEntry{page % ::paging::entriesNumber};
		BOOTSTRAP_FILL_ENTRY(pageTable[tableEntry], page * ::paging::pageSize, kernelPagingFlags);
	}
}

} // namespace paging

} // namespace boot
