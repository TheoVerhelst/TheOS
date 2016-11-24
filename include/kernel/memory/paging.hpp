#ifndef PAGING_HPP
#define PAGING_HPP

#include <cstdint>
#include <kernel/memory/Byte.hpp>

/// \addtogroup Kernel
/// \{

namespace paging
{

/// The number of entries in a page table or in the page directory.
constexpr size_t entriesNumber{1024};

/// The size of a page, in bytes.
constexpr size_t pageSize{4096};

/// The quantity of memory that a page table maps when used, in bytes.
constexpr size_t pageTableCoverage{entriesNumber * pageSize};

/// The address of the end of the lower memory, i.e. the memory
/// before the 1Mo limit. Lower memory shouldn't be used, since only
/// a very short part is usable (about 640Ko).
constexpr uintptr_t lowerMemoryLimit{0x100000};

/// The offset between the physical and te logical location of the kernel in the
/// memory. This value is defined in the linker script, but we redefine it here
/// in order to be able to use it as a constexpr (such as for array sizing).
constexpr size_t kernelVirtualOffset{0xC0000000};

/// Arbitrary number (yet another) that is the supposed maximum number of page
/// tables that the kernel would need to map itself. 16 page tables allows to
/// have a kernel image of 64Mb at max.
constexpr size_t kernelPageTablesNumber{16};

namespace Flags
{

enum Flags : uint16_t
{
	Present        = 1 << 0,
	ReadWrite      = 1 << 1,
	UserSupervisor = 1 << 2,
	WriteTrough    = 1 << 3,
	CacheDisabled  = 1 << 4,
	Accessed       = 1 << 5,
	Dirty          = 1 << 6,// Only for page table entry
	PageSize       = 1 << 7,// Only for page directory entry
	Global         = 1 << 8,
	OSFlag0        = 1 << 9,
	OSFlag1        = 1 << 10,
	OSFlag2        = 1 << 11,
};

}// namespace Flags

/// An entry in a page table that points to a physical page of the memory.
class PageTableEntry
{
	public:
		/// Default constructor.
		/// \param address The address of the physical page.
		/// \param flags Various flags of the page.
		PageTableEntry(Byte* physicalAddress = nullptr, uint16_t flags = 0);

		/// Sets attributes values.
		/// \param address The address of the physical page.
		/// \param flags Various flags of the page.
		void set(Byte* physicalAddress = nullptr, uint16_t flags = 0);

	private:
		uint32_t _physicalAddress : 20;///< The address of the physical page.
		uint16_t _flags : 12;          ///< Various flags of the page.
};
static_assert(sizeof(PageTableEntry) == 4, "PageTableEntry must be 32-bit.");

/// An entry in the page directoy, it points to a specific page table.
class PageDirectoryEntry
{
	public:
		/// Default constructor.
		/// \param pageTable The pointer to the page table.
		/// \param flags Various flags about the page directory entry.
		PageDirectoryEntry(PageTableEntry* pageTable = nullptr, uint16_t flags = 0);

		/// Sets attributes values.
		/// \param pageTable The pointer to the page table.
		/// \param flags Various flags about the page directory entry.
		void set(PageTableEntry* pageTable = nullptr, uint16_t flags = 0);

	private:
		uint32_t _pageTable : 20;///< The pointer to the page table.
		uint16_t _flags : 12;    ///< Various flags about the page directory entry.
};
static_assert(sizeof(PageDirectoryEntry) == 4, "PageDirectoryEntry must be 32-bit.");

/// Get the first 4k-aligned address that is greater or equal to
/// \a address.
/// \param address The address to convert.
/// \return The first 4k-aligned address that is greater or equal to
/// \a address.
constexpr Byte* alignUp(Byte* address);

/// Get the first 4k-aligned address that is less or equal to
/// \a address.
/// \param address The address to convert.
/// \return The first 4k-aligned address that is less or equal to
/// \a address.
constexpr Byte* alignDown(Byte* address);

/// This is a namespace that includes all functions and structures used in the
/// early initialization of the kernel (when paging is not yet enabled).
/// The job of these guys is in fact to enable paging.
///
/// This is why they have special compiler directive: they need to be
/// linked in special sections that are not in the higher half.
///
/// And because of this, we cannot use the classes above, because the text of
/// the methods is linked in the higher half.
namespace bootstrap
{

/// Help to fill an entry with the proper address and flags.
/// \param entry The lvalue representing the page {table|directory} entry to
/// fill.
/// \param address The address to put in the entry.
/// \param flags The flags to put in the entry, they must already be OR'ed.
/// \example FILL_ENTRY(pageDirectory[0], anAddress, Flags::Present | Flags::ReadWrite);
#define BOOTSTRAP_FILL_ENTRY(entry, address, flags)                            \
	entry = (reinterpret_cast<uint32_t>(address) & 0xFFFFF000) | (flags & 0xFFF)

#define BOOTSTRAP_ALIGN_UP(address)                                            \
	reinterpret_cast<Byte*>((reinterpret_cast<uintptr_t>(address) + pageSize - 1) & ~(pageSize - 1))

#define BOOTSTRAP_ALIGN_DOWN(address)                                          \
	reinterpret_cast<Byte*>(reinterpret_cast<uintptr_t>(address) & ~(pageSize - 1))

/// The page directory that is primarily used by the kernel, when the paging is
/// enabled .
extern "C" alignas(pageSize) [[gnu::section(".pagingTables")]] uint32_t kernelPageDirectory[entriesNumber];
static_assert(sizeof(kernelPageDirectory) == pageSize, "The page directory must fit in one frame.");

/// The page tables used to map the kernel.
alignas(pageSize) [[gnu::section(".pagingTables")]] extern uint32_t kernelPageTables[kernelPageTablesNumber][entriesNumber];
static_assert(sizeof(kernelPageTables[0]) == pageSize, "The page table must fit in one frame.");

extern "C" void* lowKernelStart;
extern "C" void* lowKernelEnd;
extern size_t usedPageTables;
constexpr uint16_t kernelPagingFlags{Flags::Present | Flags::ReadWrite | Flags::UserSupervisor};

/// Initializes the kernel paging by just setting up the page directory and the
/// page tables. The assembly operations (modifying CR3 or whatever) are not
/// done here, but rather in the assembly routine that is calling this function.
extern "C" [[gnu::section(".bootInit")]] void initKernelPaging();

[[gnu::section(".bootInit")]] void mapMemory(Byte* start, Byte* end, bool higherHalf);

}// namespace bootstrap

constexpr Byte* alignUp(Byte* address)
{
	const uintptr_t uintAddress{reinterpret_cast<uintptr_t>(address)};
	return reinterpret_cast<Byte*>((uintAddress + paging::pageSize - 1) & ~(paging::pageSize - 1));
}

constexpr Byte* alignDown(Byte* address)
{
	const uintptr_t uintAddress{reinterpret_cast<uintptr_t>(address)};
	return reinterpret_cast<Byte*>(uintAddress & ~(paging::pageSize - 1));
}

}// namespace paging

/// \}

#endif// PAGING_HPP
