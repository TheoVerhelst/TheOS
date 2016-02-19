#ifndef IDT_HPP
#define IDT_HPP

#include <cstdint>
#include <cstddef>

namespace idt
{

void initializeIdt();

enum Flags : uint8_t
{
	Ring0 = 0,
	Ring1   = 1,
	Ring2   = 2,
	Ring3   = 3,
	Present = 1 << 2
};

enum GateSelector : uint16_t
{
	TaskGate      = 5 << 8,
	InterruptGate = 6 << 8,
	TrapGate      = 7 << 8,
	Size          = 1 << 11///< Set for 32-bit sized gate, unset for 16-bit.
};

enum Segment : uint16_t
{
	Code = 0x10,
	Data = 0x08
};

struct IdtEntry
{
	public:
		IdtEntry(uint32_t base = 0);

	private:
		uint16_t _base0;
		uint16_t _segment;
		uint16_t _gateSelector:13;
		uint8_t _flags:3;
		uint16_t _base1;
} __attribute__((packed));
static_assert(sizeof(IdtEntry) == 8, "And IDT entry must be 8-bytes long.");

struct IdtDescriptor
{
	uint16_t size;
	uint32_t address;
} __attribute__((packed));
static_assert(sizeof(IdtDescriptor) == 6, "The IDT descriptor must be 6-bytes long.");

constexpr size_t idtSize{64};

extern IdtEntry idt[idtSize];

extern IdtDescriptor idtDescriptor;

}// namespace idt

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void isr32();
extern "C" void isr33();
extern "C" void isr34();
extern "C" void isr35();
extern "C" void isr36();
extern "C" void isr37();
extern "C" void isr38();
extern "C" void isr39();
extern "C" void isr40();
extern "C" void isr41();
extern "C" void isr42();
extern "C" void isr43();
extern "C" void isr44();
extern "C" void isr45();
extern "C" void isr46();
extern "C" void isr47();
extern "C" void isr48();
extern "C" void isr49();
extern "C" void isr50();
extern "C" void isr51();
extern "C" void isr52();
extern "C" void isr53();
extern "C" void isr54();
extern "C" void isr55();
extern "C" void isr56();
extern "C" void isr57();
extern "C" void isr58();
extern "C" void isr59();
extern "C" void isr60();
extern "C" void isr61();
extern "C" void isr62();
extern "C" void isr63();

#endif// IDT_HPP
