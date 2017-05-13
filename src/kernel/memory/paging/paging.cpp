#include <kernel/memory/paging/paging.hpp>

namespace paging
{

PageTableEntry::PageTableEntry(void* frameAddress, uint16_t flags):
	_frameAddress{reinterpret_cast<uint32_t>(frameAddress) >> 12},
	_flags{flags}
{
}

void* PageTableEntry::getFrameAddress() const
{
	return reinterpret_cast<void*>(_frameAddress << 12);
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

PageTableEntry* PageDirectoryEntry::getPageTableAddress() const
{
	return reinterpret_cast<PageTableEntry*>(_pageTable << 12);
}

uint16_t PageDirectoryEntry::getFlags() const
{
	return _flags;
}

} // namespace paging
