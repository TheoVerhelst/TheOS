#ifndef BOOTSTRAP_HPP
#define BOOTSTRAP_HPP

#include <std/cstddef>
#include <kernel/memory/paging/paging.hpp>

namespace paging
{

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

/// Arbitrary number (yet another) that is the supposed maximum number of page
/// tables that the kernel would need to map itself. 16 page tables allows to
/// have a kernel image of 64Mb at max.
constexpr size_t kernelPageTablesNumber{16};

/// Help to fill an entry with the proper address and flags.
/// \param entry The lvalue representing the page {table|directory} entry to
/// fill.
/// \param address The address to put in the entry.
/// \param flags The flags to put in the entry, they must already be OR'ed.
/// \example FILL_ENTRY(pageDirectory[0], anAddress, Flags::Present | Flags::ReadWrite);
#define BOOTSTRAP_FILL_ENTRY(entry, address, flags)                            \
	entry = (reinterpret_cast<uint32_t>(address) & 0xFFFFF000) | (flags & 0xFFF)

#define BOOTSTRAP_ALIGN_UP(address)                                            \
	((reinterpret_cast<intptr_t>(address) + pageSize - 1UL) & ~(pageSize - 1UL))

#define BOOTSTRAP_ALIGN_DOWN(address)                                          \
	(reinterpret_cast<intptr_t>(address) & ~(pageSize - 1UL))

/// The page directory that is primarily used by the kernel, when the paging is
/// enabled .
extern "C" alignas(pageSize) [[gnu::section(".kernelPaging")]]
uint32_t kernelPageDirectory[entriesNumber];
static_assert(sizeof(kernelPageDirectory) == pageSize, "The page directory must fit in one page.");

/// The page tables used to map the kernel.
alignas(pageSize) [[gnu::section(".kernelPaging")]] extern
uint32_t kernelPageTables[kernelPageTablesNumber][entriesNumber];
static_assert(sizeof(kernelPageTables[0]) == pageSize, "The page tables must fit in one page.");

extern "C" void* lowKernelStart;
extern "C" void* lowKernelEnd;
extern size_t usedPageTables;
constexpr uint16_t kernelPagingFlags{Flags::Present | Flags::ReadWrite | Flags::UserSupervisor};

/// Initializes the kernel paging by just setting up the page directory and the
/// page tables. The assembly operations (modifying CR3 or whatever) are not
/// done here, but rather in the assembly routine that calls this function.
extern "C" [[gnu::section(".bootInit")]]
void initKernelPaging();

[[gnu::section(".bootInit")]]
void mapMemory(intptr_t start, intptr_t end, bool higherHalf);

} // namespace bootstrap

} // namespace paging

#endif // BOOTSTRAP_HPP
