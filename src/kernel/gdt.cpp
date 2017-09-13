#include <kernel/gdt.hpp>

gdt::GdtDescriptor descriptor;

namespace gdt
{

SegmentDescriptor globalDescriptorTable[3];

SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags0, uint8_t flags1):
	_limit0{static_cast<uint16_t>(limit & 0x0000FFFF)},
	_base0{static_cast<uint16_t>(base & 0x0000FFFF)},
	_base1{static_cast<uint8_t>((base & 0x00FF0000) >> 16)},
	_flags0{flags0},
	_limit1AndFlags1{static_cast<uint8_t>(((limit & 0x000F0000) >> 16) | flags1)},
	_base2{static_cast<uint8_t>((base & 0xFF000000) >> 24)}
{
}

void initializeGdt()
{
	descriptor._address = reinterpret_cast<uint32_t>(&globalDescriptorTable);
	descriptor._size = sizeof(globalDescriptorTable);
	globalDescriptorTable[1] = SegmentDescriptor(0, 0xFFFFF,
			Flags0::Enabled | Flags0::DataOrCode | Flags0::DescriptorType | Flags0::Present,
			Flags1::Size);
	globalDescriptorTable[2] = SegmentDescriptor(0, 0xFFFFF,
			Flags0::Enabled | Flags0::DescriptorType | Flags0::Present,
			Flags1::Size);
	flushGdt();
}

} // namespace gdt
