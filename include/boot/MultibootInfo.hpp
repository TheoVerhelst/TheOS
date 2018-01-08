#ifndef MULTIBOOTINFO_HPP
#define MULTIBOOTINFO_HPP

#include <std/cstdint>
#include <std/cstddef>

/// Contains structs related to the Multiboot Specification version 0.6.96,
/// which is applied by the bootloader used by the kernel.
namespace multiboot
{

/// Structure representing data about the a.out symbol table of the kernel.
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
/// See the Executable and Linkable Format (ELF) specification for more
/// informations.
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
	/// Size of the structure (may be greater than sizeof(MemoryRegion)).
	size_t size;

	/// Address of the first byte of the region.
	uint64_t base_addr;

	/// Length of the region.
	uint64_t length;

	/// Contains _validType if the region is available for use, any other value
	/// otherwise.
	uint32_t type;

	/// The value for _type that indicates a valid memory region.
	static constexpr uint32_t validType {UINT32_C(1)};
};

/// This is the Multiboot information data structure,
/// through which the boot loader communicates vital information to the
/// operating system. The operating system can use or ignore any parts of the
/// structure as it chooses; all information passed by the boot loader is
/// advisory only.
struct MultibootInfo
{
	static_assert(sizeof(void*) == sizeof(uint32_t), "Addresses must be 32-bit");
	static_assert(sizeof(size_t) == sizeof(uint32_t), "Sizes must be 32-bit");

	/// Indicates the presence and the validity of the following fields.
	uint32_t flags;

	/// Amount of lower memory, in kilobytes.
	size_t mem_lower;

	/// Amount of upper memory, in kilobytes.
	size_t mem_upper;

	 /// Indicates which bios disk device the boot loader loaded the OS image
	 /// from.
	uint32_t boot_device;

	/// Command line to be passed to the kernel.
	char* cmdline;

	/// Number of modules loaded.
	size_t mods_count;

	/// Physical address of the first module structure.
	void* mods_addr;
	union
	{
		/// Data about the a.out symbol table of the kernel.
		AOutSyms a_out_syms;

		/// Data about the elf32 symbol table of the kernel.
		Elf32Syms elf32_syms;
	};

	/// Size of the memory map.
	size_t mmap_length;

	/// Address of the first memory map entry.
	MemoryRegion* mmap_addr;

	/// Size of the drives structure.
	size_t drives_length;

	/// Address of the first drives structure entry.
	void* drives_addr;

	/// Address of the rom configuration table returned by the GET CONFIGURATION
	/// bios call.
	uint32_t config_table;

	/// Name of the bootloader.
	char* boot_loader_name;

	/// Address of an APM table. See Advanced Power Management (APM) BIOS
	/// Interface Specification, for more information.
	void* apm_table;

	/// Addresses of VBE control information returned by the VBE Function 00h.
	uint32_t vbe_control_info;

	/// Addresses of VBE mode information returned by the VBE Function 01h.
	uint32_t vbe_mode_info;

	/// Current video mode in the format specified in VBE 3.0.
	uint16_t vbe_mode;

	/// The table of a protected mode interface as defined in VBE 2.0+.
	uint16_t vbe_interface_seg;

	/// The table of a protected mode interface as defined in VBE 2.0+.
	uint16_t vbe_interface_off;

	/// The table of a protected mode interface as defined in VBE 2.0+.
	uint32_t vbe_interface_len;
};

/// Namespace of the enumeration used to test the flag attribute in
/// MultibootInfo.
namespace InfoAvailable
{

/// Enumeration used to test the flag attribute in MultibootInfo.
enum InfoAvailable : uint32_t
{
	/// Indicates that _mem_upper and _mem_lower are valid.
	mem_bounds       = 1 << 0,

	/// Indicates that _boot_device is valid.
	boot_device      = 1 << 1,

	/// Indicates that _cmdline is valid.
	cmdline          = 1 << 2,

	/// Indicates that _mods_count and _mods_addr are valid.
	mods             = 1 << 3,

	/// Indicates that _a_out_syms is valid.
	/// \note a_out_syms and elf32_syms are mutually exclusive.
	a_out_syms       = 1 << 4,

	/// Indicates that _elf32_syms is valid.
	elf32_syms       = 1 << 5,

	/// Indicates that _mmap_length and _mmap_addr are valid.
	mmap             = 1 << 6,

	/// Indicates that _drives_length and _drives_addr are valid.
	drives           = 1 << 7,

	/// Indicates that _config_table is valid.
	config_table     = 1 << 8,

	/// Indicates that _boot_loader_name is valid.
	boot_loader_name = 1 << 9,

	/// Indicates that _apm_table is valid.
	apm_table        = 1 << 10,

	/// Indicates that all _vbe_* attributes are valid.
	vbe              = 1 << 11
};

} // namespace InfoAvailable

} // namespace multiboot

#endif // MULTIBOOTINFO_HPP

