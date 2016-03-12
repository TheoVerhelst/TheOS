#ifndef IDT_HPP
#define IDT_HPP

#include <cstdint>
#include <cstddef>
#include <kernel/interrupts/pic.hpp>

/// \addtogroup Kernel
/// \{

namespace idt
{

void initializeIdt();

namespace Interrupt
{

enum Interrupt : uint32_t
{
	DivideError = 0,
	DebugException,
	NmiInterrupt,
	BreakPoint,
	Overflow,
	BoundRangeException,
	InvalidOpcode,
	DeviceNotAvailable,
	DoubleFault,
	CoprocessorSegmentOverrun,
	InvalidTss,
	SegmentNotPresent,
	GeneralProtection,
	PageFault,
	X87FpuFloatingPointError,
	AlignementCheck,
	MachineCheck,
	SimdFloatingPointException,
	VirtualizationException,
	IntelReserved,
	Timer = pic::masterOffset,
	Keyboard,
	Cascade,
	Com2,
	Com1,
	Lpt2,
	FloppyDisk,
	Lpt1,
	CmosClock = pic::slaveOffset,
	FreeIrq1,
	FreeIrq2,
	FreeIrq3,
	Ps2Mouse,
	Fpu,
	PrimaryAtaHdd,
	SecondaryAtaHdd
};

}// namespace Interrupt

namespace Flags
{

enum Flags : uint8_t
{
	Ring0 = 0,
	Ring1   = 1,
	Ring2   = 2,
	Ring3   = 3,
	Present = 1 << 2
};

}// namespace Flags

namespace GateSelector
{

enum GateSelector : uint16_t
{
	TaskGate      = 5 << 8,
	InterruptGate = 6 << 8,
	TrapGate      = 7 << 8,
	Size          = 1 << 11///< Set for 32-bit sized gate, unset for 16-bit.
};

}// namespace GateSelector

namespace Segment
{

enum Segment : uint16_t
{
	Code = 0x10,
	Data = 0x08
};

}// namespace Segment

struct [[gnu::packed]] IdtEntry
{
	public:
		IdtEntry(uint32_t base = 0);

	private:
		uint16_t _base0;
		uint16_t _segment;
		uint16_t _gateSelector:13;
		uint8_t _flags:3;
		uint16_t _base1;
};
static_assert(sizeof(IdtEntry) == 8, "And IDT entry must be 8-bytes long.");

struct [[gnu::packed]] IdtDescriptor
{
	uint16_t _size;
	uint32_t _address;
};
static_assert(sizeof(IdtDescriptor) == 6, "The IDT descriptor must be 6-bytes long.");

constexpr size_t idtSize{64};

extern IdtEntry idt[idtSize];

extern IdtDescriptor idtDescriptor;

}// namespace idt

// Declare all 64 ISR handler with the item trick
#define ITEM(INDEX) extern "C" void isr##INDEX();
#include <kernel/item64Helper.itm>
#undef ITEM

/// \}

#endif// IDT_HPP
