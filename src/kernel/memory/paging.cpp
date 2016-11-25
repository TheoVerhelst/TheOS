#include <kernel/memory/paging.hpp>
#include <kernel/memory/PhysicalMemoryManager.hpp>

extern "C" void test()
{
	unsigned char c{'\x0'};
	unsigned int i{0u};
	uint16_t* vgaBuffer{reinterpret_cast<uint16_t*>(0xB8000)};
	while(i < 25*80)
		vgaBuffer[i++] = static_cast<uint16_t>(c++) | UINT16_C(0x0200);
}

extern "C" void test2()
{
	unsigned char c{'\x0'};
	unsigned int i{0u};
	uint16_t* vgaBuffer{reinterpret_cast<uint16_t*>(0xB8000)};
	while(true)
	{
		vgaBuffer[i++] = static_cast<uint16_t>(c++) | UINT16_C(0x0200);
		if(i > 25*80)
			i = 0;
	}
}

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

	for(size_t i{0}; i < 8; ++i)
	{
		kernelPageDirectory[i] = (reinterpret_cast<uintptr_t>(kernelPageTables + i) & 0xFFFFF000) | kernelPagingFlags;
		for(size_t j{0}; j < entriesNumber; ++j)
			kernelPageTables[i][j] = ((i * entriesNumber + j) * pageSize) | kernelPagingFlags;
	}

	for(size_t i{8}; i < 16; ++i)
	{
		kernelPageDirectory[i-8 + (kernelVirtualOffset / pageTableCoverage)] = (reinterpret_cast<uintptr_t>(kernelPageTables + i) & 0xFFFFF000) | kernelPagingFlags;
		for(size_t j{0}; j < entriesNumber; ++j)
			kernelPageTables[i][j] = (((i-8) * entriesNumber + j) * pageSize) | kernelPagingFlags;
	}

	// map lower memory
	//mapMemory(reinterpret_cast<Byte*>(0), reinterpret_cast<Byte*>(16*1024*4096), false);

	// map low kernel
	//mapMemory(reinterpret_cast<Byte*>(&lowKernelStart), reinterpret_cast<Byte*>(&lowKernelEnd), false);

	// map higher half kernel
	//mapMemory(reinterpret_cast<Byte*>(&kernelPhysicalStart), reinterpret_cast<Byte*>(&kernelPhysicalEnd), true);
}

[[gnu::section(".bootInit")]] void mapMemory(Byte* start, Byte* end, bool higherHalf)
{
	// Difference of indexes between a page table in the page tables array
	// and the matching entry in the page directory
	const size_t offset{higherHalf ? kernelVirtualOffset / pageTableCoverage : 0};

	const uint32_t castedStart{reinterpret_cast<uintptr_t>(BOOTSTRAP_ALIGN_DOWN(start))};
	const uint32_t castedEnd{reinterpret_cast<uintptr_t>(BOOTSTRAP_ALIGN_UP(end))};

	// Loop over the page directory entries to initialize them
	// i is the index of the current page directory entry
	for(size_t i{castedStart / pageTableCoverage}; i < (castedEnd == 0 ? 0 : ((castedEnd - 1) / pageTableCoverage) + 1); ++i)
		if(not (kernelPageDirectory[i + offset] & Flags::Present))
			BOOTSTRAP_FILL_ENTRY(kernelPageDirectory[i + offset], &(kernelPageTables[usedPageTables++]), kernelPagingFlags);

	// Loop over the page table entries to initialize them
	// i is the frame number in the whole memory (e.g. when i == 2, we are
	// initializing the frame starting at 0x2000)
	for(size_t i{castedStart / pageSize}; i < (castedEnd == 0 ? 0 : ((castedEnd - 1) / pageSize) + 1); ++i)
	{
		size_t pageDirectoryIndex{(i / entriesNumber) + offset};
		size_t pageTableIndex{i % entriesNumber};
		if(kernelPageDirectory[pageDirectoryIndex] & Flags::Present)
		{
			uint32_t* pageTable{reinterpret_cast<uint32_t*>(kernelPageDirectory[pageDirectoryIndex] & 0xFFFFF000)};
			BOOTSTRAP_FILL_ENTRY(pageTable[pageTableIndex], i * pageSize, kernelPagingFlags);
		}
		else
			test2();
	}
}

}// namespace bootstrap

}// namespace paging
