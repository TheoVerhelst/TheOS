#ifndef IDT_HPP
#define IDT_HPP

#include <cstdint>
#include <cstddef>
#include <kernel/interrupts/pic.hpp>

/// \addtogroup Kernel
/// \{

/// Namespace related to the managing of the Interrupt Descriptor Table (IDT).
/// An interrupt descriptor is a structure indicating where is located an
/// interrupt handler, among other things.
namespace idt
{

/// Set up the IDT.
void initializeIdt();

/// Namespace of the numeration of all interrupts that can arise.
namespace Interrupt
{

/// Enumeration of all interrupts that can arise.
enum Interrupt : uint32_t
{
	/// Divide error.
	/// **Source:** DIV and IDIV instructions.
	DivideError = 0,

	/// Debug exception.
	/// **Source:** instruction, data, and I/O breakpoints; single-step; and others.
	DebugException,

	/// NMI interrupt.
	/// **Source:** nonmaskable external interrupt.
	NmiInterrupt,

	/// Break point.
	/// **Source:** INT 3 instruction.
	BreakPoint,

	/// Overflow.
	/// **Source:** INTO instruction.
	Overflow,

	/// Bound range exception.
	/// **Source:** BOUND instruction.
	BoundRangeException,

	/// Invalid opcode.
	/// **Source:** UD2 instruction or reserved opcode.
	InvalidOpcode,

	/// Device not available.
	/// **Source:** floating-point or WAIT/FWAIT instruction.
	DeviceNotAvailable,

	/// Double fault.
	/// **Source:** any instruction that can generate an exception, an NMI, or an
	/// INTR.
	DoubleFault,

	/// Coprocessor segment overrun.
	/// **Source:** floating-point instruction.
	CoprocessorSegmentOverrun,

	/// Invalid TSS.
	/// **Source:** task switch or TSS access.
	InvalidTss,

	/// Segment not present.
	/// **Source:** loading segment registers or accessing system segments.
	SegmentNotPresent,

	/// Stack segment fault.
	/// **Source:** stack operations and SS register loads.
	StackSegmentFault,

	/// General protection.
	/// **Source:** any memory reference and other protection checks.
	GeneralProtection,

	/// Page fault.
	/// **Source:** any memory reference.
	PageFault,

	/// X87 FPU floating point error.
	/// **Source:** x87 FPU floating-point or WAIT/FWAIT instruction.
	X87FpuFloatingPointError,

	/// Alignement check.
	/// **Source:** any data reference in memory.
	AlignementCheck,

	/// Machine check.
	/// **Source:** error codes (if any) and source are model dependent.
	MachineCheck,

	/// SIMD floating point exception.
	/// **Source:** SSE/SSE2/SSE3 floating-point instructions.
	SimdFloatingPointException,

	/// Virtualization exception.
	/// **Source:** EPT violations.
	VirtualizationException,

	/// Intel reserved.
	/// **Source:**
	IntelReserved,

	/// This is the first master Programmable Interrupt, so this is why it has a
	/// specific value.
	/// Timer.
	/// **Source:** the CPU clock.
	Timer = pic::masterOffset,

	/// Keyboard.
	/// **Source:** any keyboard event.
	Keyboard,

	/// Cascade PIC entry, not an interrupt.
	Cascade,

	/// \todo Document this.
	Com2,

	/// \todo Document this.
	Com1,

	/// \todo Document this.
	Lpt2,

	/// \todo Document this.
	FloppyDisk,

	/// \todo Document this.
	Lpt1,

	/// This is the first slave Programmable Interrupt, this is why it has a
	/// specific value.
	/// \todo Document this.
	CmosClock = pic::slaveOffset,

	/// An IRQ that is assignable by the PIC.
	FreeIrq1,

	/// An IRQ that is assignable by the PIC.
	FreeIrq2,

	/// An IRQ that is assignable by the PIC.
	FreeIrq3,

	/// PS/2 mouse event.
	/// **Source:** any PS/2 mouse event.
	Ps2Mouse,

	/// \todo Document this.
	Fpu,

	/// \todo Document this.
	PrimaryAtaHdd,

	/// \todo Document this.
	SecondaryAtaHdd
};

}// namespace Interrupt

/// Namespace of the flags to put in an interrupt descriptor.
namespace Flags
{

/// Flags to put in an interrupt descriptor.
enum Flags : uint8_t
{
	Ring0 = 0,
	Ring1   = 1,
	Ring2   = 2,
	Ring3   = 3,
	Present = 1 << 2
};

}// namespace Flags

/// Namespace for the gate selector values.
namespace GateSelector
{

/// Bit patterns to put in the interrupt descriptor indicating which kind of
/// interrupt handler it is.
enum GateSelector : uint16_t
{
	TaskGate      = 5 << 8,///< Task gate.
	InterruptGate = 6 << 8,///< Interrupt gate (the most common).
	TrapGate      = 7 << 8,///< Trap gate.
	Size          = 1 << 11///< Set for 32-bit sized gate, unset for 16-bit.
};

}// namespace GateSelector

/// Namespace for the segment selector values.
namespace Segment
{

/// Indicates which kind of segment the interrupt handler belongs to.
enum Segment : uint16_t
{
	Code = 0x10,
	Data = 0x08
};

}// namespace Segment

/// An entry in the IDT, i.e. an interrupt descriptor.
struct [[gnu::packed]] IdtEntry
{
	public:
		/// Constructor.
		/// \param base The address of the interrupt handler.
		IdtEntry(uint32_t base = 0);

	private:
		/// First part of the address of the interrupt handler.
		uint16_t _base0;

		/// Indicates in which segment the entry belongs to.
		uint16_t _segment;

		/// Indicates the kind of interrupt descriptor.
		uint16_t _gateSelector:13;

		/// Some flags indicating if the interrupt handler is present and its
		/// privilege level.
		uint8_t _flags:3;

		/// Second part of the address of the interrupt handler.
		uint16_t _base1;
};
static_assert(sizeof(IdtEntry) == 8, "And IDT entry must be 8-bytes long.");

/// Structure to gives to the CPU indicating where is located the IDT.
struct [[gnu::packed]] IdtDescriptor
{
	uint16_t _size;   ///< Size of the IDT in bytes, minus 1.
	uint32_t _address;///< Address of the IDT.
};
static_assert(sizeof(IdtDescriptor) == 6, "The IDT descriptor must be 6-bytes long.");

/// Number of handlers in the IDT.
constexpr size_t idtSize{64};

/// The so-called IDT.
extern IdtEntry idt[idtSize];

/// The descriptor of the IDT to give to the CPU.
extern IdtDescriptor idtDescriptor;

}// namespace idt

/// Declare all 64 ISR handler with the item trick
#define ITEM(INDEX) extern "C" void isr##INDEX();
#include <kernel/item64Helper.itm>
#undef ITEM

/// \}

#endif// IDT_HPP
