#include <kernel/interrupts/IDT.hpp>

namespace idt
{

void setupIdt()
{
#define MAKE_IDT_ENTRY(INDEX) idt[INDEX] = IdtEntry(reinterpret_cast<uint32_t>(&isr##INDEX))
	MAKE_IDT_ENTRY(0);
	MAKE_IDT_ENTRY(1);
	MAKE_IDT_ENTRY(2);
	MAKE_IDT_ENTRY(3);
	MAKE_IDT_ENTRY(4);
	MAKE_IDT_ENTRY(5);
	MAKE_IDT_ENTRY(6);
	MAKE_IDT_ENTRY(7);
	MAKE_IDT_ENTRY(8);
	MAKE_IDT_ENTRY(9);
	MAKE_IDT_ENTRY(10);
	MAKE_IDT_ENTRY(11);
	MAKE_IDT_ENTRY(12);
	MAKE_IDT_ENTRY(13);
	MAKE_IDT_ENTRY(14);
	MAKE_IDT_ENTRY(15);
	MAKE_IDT_ENTRY(16);
	MAKE_IDT_ENTRY(17);
	MAKE_IDT_ENTRY(18);
	MAKE_IDT_ENTRY(19);
	MAKE_IDT_ENTRY(20);
	MAKE_IDT_ENTRY(21);
	MAKE_IDT_ENTRY(22);
	MAKE_IDT_ENTRY(23);
	MAKE_IDT_ENTRY(24);
	MAKE_IDT_ENTRY(25);
	MAKE_IDT_ENTRY(26);
	MAKE_IDT_ENTRY(27);
	MAKE_IDT_ENTRY(28);
	MAKE_IDT_ENTRY(29);
	MAKE_IDT_ENTRY(30);
	MAKE_IDT_ENTRY(31);
#undef MAKE_IDT_ENTRY

	// Give the idtDescriptor address to the instruction lidt
	__asm__ __volatile__ ("lidt %0":: "m"(idtDescriptor));
}

IdtEntry::IdtEntry(uint32_t base):
	_base0{static_cast<uint16_t>(base & 0x0000FFFF)},
	_segment{Segment::code},
	_padding{GateSelector::InterruptGate & GateSelector::Size},
	_flags{Flags::Present & Flags::Ring0},
	_base1{static_cast<uint16_t>((base & 0xFFFF0000) >> 16)}
{
}

}// namespace idt
