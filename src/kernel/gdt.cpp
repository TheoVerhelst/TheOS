#include <kernel/gdt.hpp>

gdt::GdtDescriptor descriptor;

namespace gdt
{

GdtEntry globalDescriptorTable[3];

GdtEntry::GdtEntry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags):
	_limit0{static_cast<uint16_t>(limit & 0x0000FFFF)},
	_base0{static_cast<uint16_t>(base & 0x0000FFFF)},
	_base1{static_cast<uint8_t>((base & 0x00FF0000) >> 16)},
	_access{access},
	_limit1{static_cast<uint8_t>((limit & 0x000F0000) >> 16)},
	_flags{flags},
	_base2{static_cast<uint8_t>((base & 0xFF000000) >> 24)}
{
}

void initializeGdt()
{
	descriptor._address = reinterpret_cast<uint32_t>(&globalDescriptorTable);
	descriptor._size = sizeof(globalDescriptorTable);
	globalDescriptorTable[1] = GdtEntry(0, 0xFFFFF,
			Access::ReadWrite | Access::Present | Access::CodeData,
			Flags::Size | Flags::Granularity);
	globalDescriptorTable[2] = GdtEntry(0, 0xFFFFF,
			Access::ReadWrite | Access::Present | Access::Execution | Access::CodeData,
			Flags::Size | Flags::Granularity);
	flushGdt();
}

} // namespace gdt
