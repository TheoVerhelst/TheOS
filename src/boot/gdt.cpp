#include <boot/segmentSelectors.hpp>
#include <boot/gdt.hpp>

namespace boot
{

namespace gdt
{

alignas(sizeof(SegmentDescriptor)) [[gnu::section(".bootBss")]]
SegmentDescriptor globalDescriptorTable[3];

[[gnu::section(".bootBss")]]
gdt::GdtDescriptor gdtDescriptor;

[[gnu::section(".bootText")]]
void initializeGdt()
{
	gdtDescriptor.address = reinterpret_cast<uint32_t>(globalDescriptorTable);
	gdtDescriptor.size = sizeof(globalDescriptorTable);
	globalDescriptorTable[0] = constructSegmentDescriptor(0, 0, 0, 0);
	globalDescriptorTable[CODE_SEGMENT >> 3] = constructSegmentDescriptor(0, 0xFFFFFFFF,
			Flags0::Enabled | Flags0::DataOrCode | Flags0::DescriptorType | Flags0::Present,
			Flags1::Size | Flags1::Granularity);
	globalDescriptorTable[DATA_SEGMENT >> 3] = constructSegmentDescriptor(0, 0xFFFFFFFF,
			Flags0::Enabled | Flags0::DescriptorType | Flags0::Present,
			Flags1::Size | Flags1::Granularity);
	flushGdt();
}

[[gnu::section(".bootText")]]
SegmentDescriptor constructSegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags0, uint8_t flags1)
{
	SegmentDescriptor result;
	result.limit0 = static_cast<uint16_t>(limit & 0x0000FFFF);
	result.base0 = static_cast<uint16_t>(base & 0x0000FFFF);
	result.base1 = static_cast<uint8_t>((base & 0x00FF0000) >> 16);
	result.flags0 = flags0;
	result.limit1AndFlags1 = static_cast<uint8_t>(((limit & 0x000F0000) >> 16) | flags1);
	result.base2 = static_cast<uint8_t>((base & 0xFF000000) >> 24);
	return result;
}

} // namespace gdt

} // namespace boot
