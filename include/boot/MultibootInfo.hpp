#ifndef MULTIBOOTINFO_HPP
#define MULTIBOOTINFO_HPP

#include <cstdint>
#include <cstddef>
#include <kernel/memory/Byte.hpp>

namespace multiboot
{

/// Structure representing data about the a.out
/// symbol table of the kernel.
/// addr is the physical address of the size (4-byte unsigned long) of an
/// array of a.out format nlist structures, followed immediately by the array
/// itself, then the size (4-byte unsigned long) of a set of zero-terminated
/// ascii strings (plus sizeof(unsigned long) in this case), and finally the
/// set of strings itself.
struct AOutSyms
{
	size_t tabsize;   ///< Size of the array.
	size_t strsize;   ///< Size of the null-terminated strings structure.
	void* addr;       ///< Address of the whole structure described above.
	uint32_t reserved;///< Reserved (probably already set to 0).
};

/// Structure representing data about the ELF32
/// symbol table of the kernel. The attributes correspond to the ‘shdr_*’
/// entries (‘shdr_num’, etc.) in the ELF specification in the program header.
/// See the Executable and Linkable Format (ELF) specification for more informations.
struct Elf32Syms
{
	uint32_t num;///< Number of entries.
	size_t size; ///< Size of each entry.
	void* addr;  ///< Address of the section header table.
	char** shndx;///< String table used as the index of names.
};

/// Structure used to represent a region of the memory that is potentially
/// available for the kernel.
struct MemoryRegion
{
	size_t size;       ///< Size of the structure (may be greater than sizeof(MemoryRegion)).
	uint64_t base_addr;///< Address of the first byte of the region.
	uint64_t length;   ///< Length of the region.
	uint32_t type;     ///< 1 if the region is available for use, any other value otherwise.
	static constexpr uint32_t validType{UINT32_C(1)};
};

/// This is the Multiboot information data structure,
/// through which the boot loader communicates vital information to the operating system.
/// The operating system can use or ignore any parts of the structure as it chooses;
/// all information passed by the boot loader is advisory only.
struct MultibootInfo
{
	static_assert(sizeof(void*) == sizeof(uint32_t), "Addresses must be 32-bit");
	static_assert(sizeof(size_t) == sizeof(uint32_t), "Sizes must be 32-bit");
	uint32_t flags;            ///< Indicates the presence and the validity of the following fields.
	size_t mem_lower;          ///< Amount of lower memory, in kilobytes.
	size_t mem_upper;          ///< Amount of upper memory, in kilobytes.
	uint32_t boot_device;      ///< Indicates which bios disk device the boot loader loaded the OS image from.
	char* cmdline;             ///< Command line to be passed to the kernel.
	size_t mods_count;         ///< Number of modules loaded.
	void* mods_addr;           ///< Physical address of the first module structure.
	union
	{
		AOutSyms a_out_syms;   ///< Data about the a.out symbol table of the kernel.
		Elf32Syms elf32_syms;  ///< Data about the elf32 symbol table of the kernel.
	};
	size_t mmap_length;        ///< Size of the memory map.
	MemoryRegion* mmap_addr;   ///< Address of the first memory map entry.
	size_t drives_length;      ///< Size of the drives structure.
	void* drives_addr;         ///< Address of the first drives structure entry.
	uint32_t config_table;     ///< Address of the rom configuration table returned by the GET CONFIGURATION bios call.
	char* boot_loader_name;    ///< Name of the bootloader.
	void* apm_table;           ///< Address of an APM table. See Advanced Power Management (APM) BIOS Interface Specification, for more information.
	uint32_t vbe_control_info; ///< Addresses of VBE control information returned by the VBE Function 00h.
	uint32_t vbe_mode_info;    ///< Addresses of VBE mode information returned by the VBE Function 01h.
	uint16_t vbe_mode;         ///< Current video mode in the format specified in VBE 3.0.
	uint16_t vbe_interface_seg;///< The table of a protected mode interface defined in VBE 2.0+.
	uint16_t vbe_interface_off;///< The table of a protected mode interface defined in VBE 2.0+.
	uint32_t vbe_interface_len;///< The table of a protected mode interface defined in VBE 2.0+.
};

/// The address of the structure, it needs to be set (in the boot assembly)
/// before the static initialization of the Kernel instance.
extern "C" const MultibootInfo* multibootInfoAddress;

namespace InfoAvailable
{

/// Enumeration used to test the flag attribute in MultibootInfo.
enum InfoAvailable : uint32_t
{
	mem_bounds       = 1 << 0,
	boot_device      = 1 << 1,
	cmdline          = 1 << 2,
	mods             = 1 << 3,
	a_out_syms       = 1 << 4,//a_out_syms and elf32_syms are mutually exclusive
	elf32_syms       = 1 << 5,
	mmap             = 1 << 6,
	drives           = 1 << 7,
	config_table     = 1 << 8,
	boot_loader_name = 1 << 9,
	apm_table        = 1 << 10,
	vbe              = 1 << 11
};

}// namespace InfoAvailable

}// namespace multiboot

#endif// MULTIBOOTINFO_HPP
