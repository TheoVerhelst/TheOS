#ifndef ISRDISPATCHER_HPP
#define ISRDISPATCHER_HPP

#include <std/cstdint>
#include <cpp/Printer.hpp>
#include <kernel/interrupts/idt.hpp>

/// Structures and functions related to the Interrupt Service Routines.
namespace isr
{

/// When an exception condition is related to a specific segment selector or IDT
/// vector, the processor pushes an error code onto the stack of the exception
/// handler (whether it is a procedure or task). The error code resembles a
/// segment selector; however, instead of a TI flag and RPL field, the error
/// code contains 3 flags:
struct [[gnu::packed]] ErrorCode
{
	// TODO do not use bit fields when ordering and packing is critical
	/// bit 0: When set, indicates that the exception occurred during delivery
	/// of an event external to the program, such as an interrupt or an earlier
	/// exception.
	/// uint8_t _externalEvent:1;

	/// bit 1: When set, indicates that the index portion of the error code
	/// refers to a gate descriptor in the IDT; when clear, indicates that the
	/// index refers to a descriptor in the GDT or the current LDT. uint8_t
	/// _descriptorLocation:1;

	/// bit 2: Only used when the IDT flag is clear. When set, the TI flag
	/// indicates that the index portion of the error code refers to a segment
	/// or gate descriptor in the LDT; when clear, it indicates that the index
	/// refers to a descriptor in the current GDT.
	/// uint8_t _gdtLdt:1;

	/// bit 3 -> 15: Provides an index into the IDT, GDT, or current LDT to the
	/// segment or gate selector being referenced by the error code.
	uint16_t _indexAndFlags;

	/// Bit reserverd for the CPU.
	uint16_t _reserved;
};
static_assert(sizeof(ErrorCode) == 4, "Error code structure must be 32-bit");

namespace Flags
{
	enum Flags : uint16_t
	{
		ExternalEvent      = 1 << 0,
		DescriptorLocation = 1 << 1,
		GdtLdt             = 1 << 2
	};
} // namespace Flags

/// Arguments that are given by the assembler routine to the ISR.
struct [[gnu::packed]] Arguments
{
	uint32_t _gs;             ///< The GS register.
	uint32_t _fs;             ///< The FS register.
	uint32_t _es;             ///< The ES register.
	uint32_t _ds;             ///< The DS register.
	uint32_t _interruptNumber;///< The index of the interrupt that occurred.
	ErrorCode _errorCode;     ///< The additional error code given by the CPU.
	uint32_t _eip;            ///< The EIP register.
	uint32_t _cs;             ///< The CS register.
	uint32_t _eflags;         ///< The flags register.
	uint32_t _useresp;        ///< The ESP register of the user.
	uint32_t _ss;             ///< The SS register.
};

/// Calls the apropriate C-written ISR, and logs the interrupt if needed.
extern "C" void isrDispatcher(Arguments args);

class Table
{
	private:
		/// Calls the apropriate C-written ISR, and logs the interrupt if
		/// needed. This function also sends a "end of interrupt" message to the
		/// PIC if needed.
		/// \param args The arguments to give to the ISR.
		friend void isrDispatcher(Arguments args);

		/// Declare all interrupts service routines with the item trick
#define ITEM(INDEX) static void isr##INDEX(Arguments args);
#include <kernel/item64Helper.itm>
#undef ITEM

		/// The table of effective ISRs.
		static constexpr void (*_table[idt::idtSize])(Arguments) =
		{
/// Assign all 64 ISR table entries with the item trick
#define ITEM(INDEX) Table::isr##INDEX,
#include <kernel/item64Helper.itm>
#undef ITEM
		};
};

/// Fancy printing of the error code to \a out.
/// \param out The printer instance.
/// \param errorCode The error code to print.
/// \return \a out.
Printer& operator<<(Printer& out, const ErrorCode& errorCode);

} // namespace isr



#endif // ISRDISPATCHER_HPP
