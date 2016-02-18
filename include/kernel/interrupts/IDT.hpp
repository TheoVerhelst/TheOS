#ifndef IDT_HPP
#define IDT_HPP

#include <cstdint>
#include <cstddef>

namespace idt
{

void setupIdt();

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
	TaskGate      = 0x005,
	InterruptGate = 0x006,
	TrapGate      = 0x007,
	Size          = 1 << 3///< Set for 32-bit sized gate, unset for 16-bit.
};

enum Segment : uint16_t
{
	code = 0x10,
	data = 0x08
};

struct IdtEntry
{
	public:
		IdtEntry(uint32_t base = 0);

	private:
		uint16_t _base0;
		uint16_t _segment;
		uint16_t _padding:13;
		uint8_t _flags:3;
		uint16_t _base1;
} __attribute__((packed));

struct IdtDescriptor
{
	uint32_t address;
	uint16_t size;
} __attribute__((packed));

constexpr size_t idtSize{32};

IdtEntry idt[idtSize];

IdtDescriptor idtDescriptor{reinterpret_cast<uint32_t>(&idt), sizeof(idt) - 1};

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

#endif// IDT_HPP
