#ifndef GDT_HPP
#define GDT_HPP

#include <std/cstdint>

namespace boot
{

namespace gdt
{

/// Global Descriptor Table Descriptor.
/// This struct simply holds the address and the size of the Global Descriptor
/// Table. A global instance of a GdtDescriptor is initialized and set,
/// then its address is given to the CPU in order to initialize segmentation.
struct [[gnu::packed]] GdtDescriptor
{
	uint16_t size;
	uint32_t address;
};
static_assert(sizeof(GdtDescriptor) == 6, "GdtDescriptor must be 6-bytes long.");

/// An entry of the Global Descriptor Table. It represents informations about
/// a segment that the CPU have to know.
/// The GDT setup is an obligatory step when booting an OS. This consists in
/// setting the segments registers correctly in order to let the CPU know
/// about the segmentation of the OS. In our case, we disable segmentation
/// by using two segments (code and data) that fit the whole memory.
/// Note that the limit and base fields are split across the structure, and
/// their parts are numbered from 0.
struct [[gnu::packed]] SegmentDescriptor
{
		/// First part of segment limit.
		uint16_t limit0;

		/// First part of base address.
		uint16_t base0;

		/// Second part of base address.
		uint8_t base1;

		/// bit 0: accessed.
		/// bit 1: enabled
		/// bit 2: "expansion-direction" if data segment (bit 3 clear), and
		/// "conforming" if code segment (bit 3 set)
		/// bit 3: 0 = data segment; 1 = code segment.
		/// bit 4 (S): Descriptor type (0 = system; 1 = code or data).
		/// bits 5 and 6 (DPL): Descriptor privilege level.
		/// bit 7 (P): Segment present.
		uint8_t flags0;

		/// bits 0 -> 3: Second part of segment limit.
		/// bit 4 (AVL): Available for use by system software.
		/// bit 5 (L): 64-bit code segment.
		/// bit 6 (D/B): Default operation size (0 = 16-bit segment; 1 = 32-bit
		/// segment).
		/// bit 6 (G): Granularity.
		uint8_t limit1AndFlags1;

		/// Third part of base address.
		uint8_t base2;
};
static_assert(sizeof(SegmentDescriptor) == 8, "SegmentDescriptor must be 8-bytes long.");

namespace Flags0
{

/// The set of bits that can be set in first flag field.
enum Flags0 : uint8_t
{
	Accessed            = 1 << 0,
	Enabled             = 1 << 1,
	DirectionConforming = 1 << 2,
	DataOrCode          = 1 << 3,
	DescriptorType      = 1 << 4,
	Privilege1          = 1 << 5,
	Privilege2          = 1 << 6,
	Present             = 1 << 7
};

} // namespace Flags0

namespace Flags1
{

/// The set of bits that can be set in the second flag field.
enum Flags1 : uint8_t
{
	AvailableForOs = 1 << 4,
	LongMode       = 1 << 5,
	Size           = 1 << 6,
	Granularity    = 1 << 7
};

} // namespace Flags1

alignas(sizeof(SegmentDescriptor)) [[gnu::section(".bootBss")]]
extern SegmentDescriptor globalDescriptorTable[3];

extern "C" [[gnu::section(".bootBss")]] gdt::GdtDescriptor gdtDescriptor;

[[gnu::section(".bootText")]] void initializeGdt();

// We use function rather than a constructor in order to prevent its code being
// in the text section in the higher half (we need it in the boot section).
[[gnu::section(".bootText")]]
SegmentDescriptor constructSegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags0, uint8_t flags1);

extern "C" [[gnu::section(".bootText")]] void flushGdt();

} // namespace gdt

} // namespace boot



#endif // GDT_HPP
