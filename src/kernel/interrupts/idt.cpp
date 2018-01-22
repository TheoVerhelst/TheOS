#include <kernel/memory/segmentation/segmentSelectors.hpp>
#include <kernel/interrupts/idt.hpp>

namespace idt
{

IdtEntry idt[idtSize];

IdtDescriptor idtDescriptor{sizeof(idt) - 1, reinterpret_cast<uint32_t>(&idt)};

void initializeIdt()
{
	// Make all 64 IDT entries with the item trick
	#define ITEM(INDEX) idt[INDEX] = IdtEntry(reinterpret_cast<uint32_t>(&isr##INDEX));
	#include <kernel/item64Helper.itm>
	#undef ITEM

	// Give the idtDescriptor address to the instruction lidt
	asm volatile("lidt %0":: "m"(idtDescriptor));
}

IdtEntry::IdtEntry(uint32_t base):
	_base0{static_cast<uint16_t>(base & 0x0000FFFF)},
	_segmentSelector{CODE_SEGMENT},
	_flags{Flags::InterruptGate | Flags::Size | Flags::Present},
	_base1{static_cast<uint16_t>((base & 0xFFFF0000) >> 16)}
{
}

} // namespace idt
