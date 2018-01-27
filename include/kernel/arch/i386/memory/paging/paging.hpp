#ifndef PAGING_HPP
#define PAGING_HPP

#include <std/cstdint>
#include <std/cstddef>

namespace paging
{

/// The number of entries in a page table or in the page directory.
constexpr size_t entriesNumber{1024};

/// The size of a page or a frame, in bytes.
constexpr size_t pageSize{4096};

/// The quantity of memory that a page table maps when fully used, in bytes.
constexpr size_t pageTableCoverage{entriesNumber * pageSize};

/// All the flags of a page directory entry or a page table entry. Undocumented
/// flags are not yet useful, and/or I don't yet understand their usage.
namespace Flags
{

enum Flags : uint32_t
{
	/// Indicates whether the entry is valid and maps a page / page table.
	Present        = 1 << 0,

	/// 0: Only read access is granted.
	/// 1: Read and write access are granted.
	ReadWrite      = 1 << 1,

	/// 0: Only supervisor can access the memory area designated by this entry.
	/// 1: User and supervisor can access the memory area designated by this
	/// entry.
	UserSupervisor = 1 << 2,

	WriteTrough    = 1 << 3,

	CacheDisabled  = 1 << 4,

	/// Indicates whether software has accessed the memory area referenced by
	/// this entry.
	Accessed       = 1 << 5,

	/// In page directory entry : ignored.
	/// In page table entry: indicates whether software has written to the
	/// memory area referenced by this entry.
	Dirty          = 1 << 6,

	/// In page directory entry: ignored.
	/// In  page table entry: reserved (must be 0).
	PageSize       = 1 << 7,

	Global         = 1 << 8,

	OSFlag0        = 1 << 9,

	OSFlag1        = 1 << 10,

	OSFlag2        = 1 << 11,
};

} // namespace Flags

/// An entry in a page table that points to a physical frame of the memory.
class PageTableEntry
{
	public:
		/// Default constructor.
		/// \param address The address of the physical frame.
		/// \param flags Various flags of the page.
		PageTableEntry(void* frameAddress, uint32_t flags);

		void* getFrameAddress() const;

		/// Gets the flags of this entry.
		/// \return The flags of this entry.
		uint32_t getFlags() const;

	private:
		/// According to Intel 386 reference, the 12 least significant bits are
		/// flags, while the 20 most significant bits are the address of the
		/// referenced frame.
		uint32_t _value;
};

/// An entry in the page directoy, it points to a specific page table.
class PageDirectoryEntry
{
	public:
		/// Default constructor.
		/// \param pageTable The pointer to the page table.
		/// \param flags Various flags about the page directory entry.
		PageDirectoryEntry(PageTableEntry* pageTable, uint32_t flags);

		PageTableEntry* getPageTableAddress() const;

		uint32_t getFlags() const;

	private:
		/// According to Intel 386 reference, the 12 least significant bits are
		/// flags, while the 20 most significant bits are the address of the
		/// referenced page table.
		uint32_t _value;
};

} // namespace paging

#endif // PAGING_HPP
