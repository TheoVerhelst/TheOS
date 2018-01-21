#ifndef IDT_HPP
#define IDT_HPP

#include <std/cstdint>
#include <std/cstddef>
#include <kernel/interrupts/pic.hpp>

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
	/// 0: Divide error.
	/// **Source:** DIV and IDIV instructions.
	DivideError = 0,

	/// 1: Debug exception.
	/// **Source:** instruction, data, and I/O breakpoints; single-step; and others.
	DebugException,

	/// 2: NMI interrupt.
	/// **Source:** nonmaskable external interrupt.
	NmiInterrupt,

	/// 3: Break point.
	/// **Source:** INT 3 instruction.
	BreakPoint,

	/// 4: Overflow.
	/// **Source:** INTO instruction.
	Overflow,

	/// 5: Bound range exception.
	/// **Source:** BOUND instruction.
	BoundRangeException,

	/// 6: Invalid opcode.
	/// **Source:** UD2 instruction or reserved opcode.
	InvalidOpcode,

	/// 7: Device not available.
	/// **Source:** floating-point or WAIT/FWAIT instruction.
	DeviceNotAvailable,

	/// 8: Double fault.
	/// **Source:** any instruction that can generate an exception, an NMI, or an
	/// INTR.
	DoubleFault,

	/// 9: Coprocessor segment overrun.
	/// **Source:** floating-point instruction.
	CoprocessorSegmentOverrun,

	/// 10: Invalid TSS.
	/// **Source:** task switch or TSS access.
	InvalidTss,

	/// 11: Segment not present.
	/// **Source:** loading segment registers or accessing system segments.
	SegmentNotPresent,

	/// 12: Stack segment fault.
	/// **Source:** stack operations and SS register loads.
	StackSegmentFault,

	/// 13: General protection.
	/// **Source:** any memory reference and other protection checks.
	GeneralProtection,

	/// 14: Page fault.
	/// **Source:** any memory reference.
	PageFault,

	/// 15: Intel reserved.
	IntelReserved0,

	/// 16: X87 FPU floating point error.
	/// **Source:** x87 FPU floating-point or WAIT/FWAIT instruction.
	X87FpuFloatingPointError,

	/// 17: Alignement check.
	/// **Source:** any data reference in memory.
	AlignementCheck,

	/// 18: Machine check.
	/// **Source:** error codes (if any) and source are model dependent.
	MachineCheck,

	/// 19: SIMD floating point exception.
	/// **Source:** SSE/SSE2/SSE3 floating-point instructions.
	SimdFloatingPointException,

	/// 20: Virtualization exception.
	/// **Source:** EPT violations.
	VirtualizationException,

	/// 21 to 31: Intel reserved.
	/// **Source:**
	IntelReserved1,

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

} // namespace Interrupt

/// Namespace of the flags to put in an interrupt descriptor.
namespace Flags
{

/// Flags to put in an interrupt descriptor.
enum Flags : uint8_t
{
	// Choose only one of these for the three first bits:
	TaskGate        = 0b101, ///< Task gate.
	InterruptGate   = 0b110, ///< Interrupt gate (the most common).
	TrapGate        = 0b111, ///< Trap gate.
	Size            = 1 << 3, ///< Set for 32-bit sized gate, unset for 16-bit.
	// Bit 4 is always 0
	PrivilegeLevel0 = 1 << 5,
	PrivilegeLevel1 = 1 << 6,
	Present         = 1 << 7
};

} // namespace Flags

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
		uint16_t _segmentSelector;

		/// Empty space, not used, must be set to 0.
		uint8_t _null = 0;

		/// Bits Indicating various information about the descriptor, to be
		/// filled with Flags.
		uint8_t _flags;

		/// Second part of the address of the interrupt handler.
		uint16_t _base1;
};
static_assert(sizeof(IdtEntry) == 8, "And IDT entry must be 8-bytes long.");

/// Structure to gives to the CPU indicating where is located the IDT.
struct [[gnu::packed]] IdtDescriptor
{
	uint16_t size;   ///< Size of the IDT in bytes, minus 1.
	uint32_t address;///< Address of the IDT.
};
static_assert(sizeof(IdtDescriptor) == 6, "The IDT descriptor must be 6-bytes long.");

/// Number of handlers in the IDT.
constexpr size_t idtSize{64};

/// The so-called IDT.
alignas(sizeof(IdtEntry)) extern IdtEntry idt[idtSize];

/// The descriptor of the IDT to give to the CPU.
extern IdtDescriptor idtDescriptor;

} // namespace idt

/// Declare all 64 ISR handler with the item trick
#define ITEM(INDEX) extern "C" void isr##INDEX();
#include <kernel/item64Helper.itm>
#undef ITEM



#endif // IDT_HPP
