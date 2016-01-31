#ifndef MULTIBOOTINFO_HPP
#define MULTIBOOTINFO_HPP

#include <stdint.h>

/// Structure representing data about the a.out
/// symbol table of the kernel.
struct AOutSyms
{
	uint32_t tabsize;
	uint32_t strsize;
	void* addr;
	uint32_t reserved;
};

/// Structure representing data about the elf32
/// symbol table of the kernel.
struct Elf32Syms
{
	uint32_t num;
	uint32_t size;
	void* addr;
	uint32_t shndx;
};

struct MemoryRegion
{
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
};

/// This is the Multiboot information data structure,
/// through which the boot loader communicates vital information to the operating system.
/// The operating system can use or ignore any parts of the structure as it chooses;
/// all information passed by the boot loader is advisory only.
struct MultibootInfo
{
	static_assert(sizeof(void*) == sizeof(uint32_t), "Addresses must be 32-bit");
	uint32_t flags;            ///< Indicates the presence and validity of the following fields.
	uint32_t mem_lower;        ///< Amount of lower memory, in kilobytes.
	uint32_t mem_upper;        ///< Amount of upper memory, in kilobytes.
	uint32_t boot_device;      ///< Indicates which bios disk device the boot loader loaded the OS image from.
	char* cmdline;             ///< Command line to be passed to the kernel.
	uint32_t mods_count;       ///< The number of modules loaded.
	void* mods_addr;           ///< Tthe physical address of the first module structure.
	union
	{
		AOutSyms a_out_syms;   ///< Present if flags[4] is set.
		Elf32Syms elf32_syms;  ///< Present if flags[5] is set.
	};
	uint32_t mmap_length;      ///< Present if flags[6] is set.
	MemoryRegion* mmap_addr;   ///< ...
	uint32_t drives_length;    ///< Present if flags[7] is set.
	void* drives_addr;         ///< ...
	uint32_t config_table;     ///< Present if flags[8] is set.
	char* boot_loader_name;    ///< Present if flags[9] is set.
	void* apm_table;           ///< Present if flags[10] is set.
	uint32_t vbe_control_info; ///< Present if flags[11] is set.
	uint32_t vbe_mode_info;    ///< ...
	uint16_t vbe_mode;         ///< ...
	uint16_t vbe_interface_seg;///< ...
	uint16_t vbe_interface_off;///< ...
	uint32_t vbe_interface_len;///< ...
};

namespace InfoAvailable
{

enum InfoAvailable : uint32_t
{
	mem_bounds       = 1 << 0,
	boot_device      = 1 << 1,
	cmdline          = 1 << 2,
	mods             = 1 << 3,
	a_out_syms       = 1 << 4,
	elf32_syms       = 1 << 5,
	mmap             = 1 << 6,
	drives           = 1 << 7,
	config_table     = 1 << 8,
	boot_loader_name = 1 << 9,
	apm_table        = 1 << 10,
	vbe              = 1 << 11
};

}// namespace InfoAvailable

#endif// MULTIBOOTINFO_HPP
