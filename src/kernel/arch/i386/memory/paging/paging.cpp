#include <kernel/arch/i386/memory/paging/paging.hpp>

namespace paging
{

PageTableEntry::PageTableEntry(void* frameAddress, uint32_t flags):
	_value{(reinterpret_cast<uint32_t>(frameAddress) & 0xFFFFF000) | (flags & 0xFFF)}
{
}

void* PageTableEntry::getFrameAddress() const
{
	return reinterpret_cast<void*>(_value & 0xFFFFF000);
}

uint32_t PageTableEntry::getFlags() const
{
	return _value & 0xFFF;
}

PageDirectoryEntry::PageDirectoryEntry(PageTableEntry* pageTable, uint32_t flags):
	_value{(reinterpret_cast<uint32_t>(pageTable) & 0xFFFFF000) | (flags & 0xFFF)}
{
}

PageTableEntry* PageDirectoryEntry::getPageTableAddress() const
{
	return reinterpret_cast<PageTableEntry*>(_value & 0xFFFFF000);
}

uint32_t PageDirectoryEntry::getFlags() const
{
	return _value & 0xFFF;
}

} // namespace paging
