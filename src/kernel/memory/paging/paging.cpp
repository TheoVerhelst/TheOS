#include <kernel/memory/paging/paging.hpp>

namespace paging
{

PageTableEntry::PageTableEntry(void* physicalAddress, uint16_t flags):
	_physicalAddress{reinterpret_cast<uint32_t>(physicalAddress) >> 12},
	_flags{flags}
{
}

uint16_t PageTableEntry::getFlags() const
{
	return _flags;
}

PageDirectoryEntry::PageDirectoryEntry(PageTableEntry* pageTable, uint16_t flags):
	_pageTable{reinterpret_cast<uint32_t>(pageTable) >> 12},
	_flags{flags}
{
}

uint16_t PageDirectoryEntry::getFlags() const
{
	return _flags;
}

} // namespace paging
