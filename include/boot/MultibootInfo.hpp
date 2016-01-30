#ifndef MULTIBOOTINFO_HPP
#define MULTIBOOTINFO_HPP

#include <stdint.h>

struct MultibootInfo
{
	uint32_t flags;            ///< Indicates the presence and validity of the following fields.
	uintptr_t mem_lower;       ///< Amount of lower memory, in kilobytes.
	uintptr_t mem_upper;       ///< Amount of upper memory, in kilobytes.
	struct
	{
		uint8_t drive;
		uint8_t part1;
		uint8_t part2;
		uint8_t part3;
	} boot_device;             ///< Indicates which bios disk device the boot loader loaded the OS image from.
	char* cmdline;             ///< Present if flags[2] is set.
	uint32_t mods_count;       ///< Present if flags[3] is set.
	uintptr_t mods_addr;       ///< ...
	union
	{
		struct
		{
			uint32_t tabsize;  ///<
			uint32_t strsize;  ///< ...
			uintptr_t addr;    ///< ...
			uint32_t reserved; ///< ...
		} a_out_syms;          ///< Present if flags[4] is set.
		struct
		{
			uint32_t num;      ///< Present if flags[5] is set.
			uint32_t size;     ///< ...
			uintptr_t addr;    ///< ...
			uint32_t shndx;    ///< ...
		} elf32_syms;          ///< ...
	};
	uint32_t mmap_length;      ///< Present if flags[6] is set.
	uintptr_t mmap_addr;       ///< ...
	uint32_t drives_length;    ///< Present if flags[7] is set.
	uintptr_t drives_addr;     ///< ...
	uint32_t config_table;     ///< Present if flags[8] is set.
	char* boot_loader_name;    ///< Present if flags[9] is set.
	uintptr_t apm_table;       ///< Present if flags[10] is set.
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
	mods          = 1 << 3,
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
