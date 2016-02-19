#ifndef GDT_HPP
#define GDT_HPP

#include <cstdint>

namespace gdt
{

/// Global Descriptor Table Descriptor.
/// This struct simply holds the address and the size of the Global Descriptor
/// Table. A global instance of a GdtDescriptor is initialized and set,
/// then its address is given to the CPU in order to initialize segmentation.
struct GdtDescriptor
{
	uint16_t size;
	uint32_t address;
} __attribute__((packed));

/// An entry of the Global Descriptor Table. It represents informations about
/// a segment that the CPU have to know.
/// The GDT setup is an obligatory step when booting an OS. This consists in
/// setting the segments registers correctly in order to let the CPU know
/// about the segmentation of the OS. In our case, we disable segmentation
/// by using two pages (code and data) that fit the whole memory.
class GdtEntry
{
	public:
		GdtEntry(uint32_t base = 0, uint32_t limit = 0, uint8_t access = 0, uint8_t flags = 0);

	private:
		uint16_t _limit0;
		uint16_t _base0;
		uint8_t _base1;
		uint8_t _access;
		uint8_t _limit1 : 4;
		uint8_t _flags : 4;
		uint8_t _base2;
} __attribute__((packed));

namespace Access
{

/// The set of bits that can be set in the access byte.
/// Note that privilege has 2 bits (it may have 4 different values).
/// See Intel documentation for complete explanations.
enum Access : uint8_t
{
	Accessed            = 1 << 0,
	ReadWrite           = 1 << 1,
	DirectionConforming = 1 << 2,
	Execution           = 1 << 3,
	CodeData            = 1 << 4,
	Privilege1          = 1 << 5,
	Privilege2          = 1 << 6,
	Present             = 1 << 7
};

}// namespace Access

namespace Flags
{

/// The set of bits that can be set in the flags half byte.
enum Flags : uint8_t
{
	SystemAvailable = 1 << 0,
	LongMode        = 1 << 1,
	Size            = 1 << 2,
	Granularity     = 1 << 3
};

}// namespace Flags

extern GdtEntry globalDescriptorTable[3];

void initializeGdt();

}// namespace gdt

extern gdt::GdtDescriptor descriptor;

extern "C" void flushGdt();

#endif// GDT_HPP
