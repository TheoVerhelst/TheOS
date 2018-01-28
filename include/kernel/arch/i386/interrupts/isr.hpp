#ifndef ISRDISPATCHER_HPP
#define ISRDISPATCHER_HPP

#include <std/cstdint>
#include <cpp/Printer.hpp>
#include <kernel/arch/i386/interrupts/idt.hpp>

/// Structures and functions related to the Interrupt Service Routines.
namespace isr
{

/// When an exception condition is related to a specific segment selector or IDT
/// vector, the processor pushes an error code onto the stack of the exception
/// handler (whether it is a procedure or task). The error code resembles a
/// segment selector; however, instead of a TI flag and RPL field, the error
/// code contains 3 flags. If the interrupt number is 14 (page fault), then the
/// error code is different. \see PageFaultErrorCode.
struct [[gnu::packed]] ErrorCode
{
	/// bit 0: When set, indicates that the exception occurred during delivery
	/// of an event external to the program, such as an interrupt or an earlier
	/// exception.
	/// uint8_t _externalEvent:1;
	///
	/// bit 1: When set, indicates that the index portion of the error code
	/// refers to a gate descriptor in the IDT; when clear, indicates that the
	/// index refers to a descriptor in the GDT or the current LDT. uint8_t
	/// _descriptorLocation:1;
	///
	/// bit 2: Only used when the IDT flag is clear. When set, the TI flag
	/// indicates that the index portion of the error code refers to a segment
	/// or gate descriptor in the LDT; when clear, it indicates that the index
	/// refers to a descriptor in the current GDT.
	/// uint8_t _gdtLdt:1;
	///
	/// bit 3 -> 15: Provides an index into the IDT, GDT, or current LDT to the
	/// segment or gate selector being referenced by the error code.
	uint16_t indexAndFlags;

	/// Bits reserverd for the CPU.
	uint16_t reserved;
};
static_assert(sizeof(ErrorCode) == 4, "ErrorCode structure must be 32-bit");

namespace Flags
{
	/// Flags for a normal error code (not for page fault). \see ErrorCode.
	enum Flags : uint16_t
	{
		ExternalEvent      = 1 << 0,
		DescriptorLocation = 1 << 1,
		GdtLdt             = 1 << 2
	};
} // namespace Flags

struct [[gnu::packed]] PageFaultErrorCode
{
	/// Bit 0: P flag. 0 If the fault was caused by a PDE or PTE without the
	/// present flag. 1 if the fault was caused by a page-level protection
	/// violation.
	///
	/// Bit 1: 0 if the fault was caused by a read, 1 if the fault was caused by
	/// a write.
	///
	/// Bit 2: 0 if the fault was caused by a supervisor mode access, 1 if the
	/// fault was caused by a user mode access.
	///
	/// Bit 3: 1 if the fault was caused by a reserved bit being set on some
	/// paging structure. 0 otherwise.
	///
	/// Bit 4: 1 if the fault was caused by an instruction fetch, 0 oteherwise.
	///
	/// Bit 5: 1 if the fault was caused by a data access to a user-mode address
	/// with protection key disallowed by the value of the PKRU register. 0
	/// otherwise.
	///
	/// Bit 15: The fault resulted from violation of SGX-specific access-control
	/// requirements (???).
	uint16_t flags;
	uint16_t reserved;
};
static_assert(sizeof(PageFaultErrorCode) == 4, "PageFaultErrorCode structure must be 32-bit");

namespace PageFaultFlags
{
	/// Flags for a page fault error code. \see PageFaultErrorCode.
	enum PageFaultFlags : uint16_t
	{
		Present          = 1 << 0,
		ReadWrite        = 1 << 1,
		SupervisorUser   = 1 << 2,
		ReservedBitSet   = 1 << 3,
		InstructionFetch = 1 << 4,
		ProtectionKey    = 1 << 5,
		Sgx              = 1 << 15
	};
} // namespace PageFaultFlags

/// Arguments that are given by the assembler routine to the ISR.
struct [[gnu::packed]] Arguments
{
	/// General registers pushed by our handler.
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;

	/// The index of the interrupt that occurred, pushed by our handler.
	uint32_t interruptNumber;

	/// The additional error code, pushed by CPU if relevant, or pushed by our
	/// handler with value 0 otherwise.
	ErrorCode errorCode;

	/// Registers pushed by the CPU.
	uint32_t eip, cs , eflags;

	/// If the interrupt comes from a higher privilege level code, the user ESP
	/// and segment selector are pushed onto the stack as well. If the interrupt
	/// comes from the same privilege level, don't touch these, they have not
	/// been pushed.
	uint32_t userEsp, ss;
};

/// Calls the apropriate C++-written ISR, and logs the interrupt if needed. This
/// function also sends a "end of interrupt" message to the PIC if needed.
/// \param args The arguments to give to the ISR.
extern "C" void isrDispatcher(Arguments& args);

/// All ISRs are put in this class in order to grant them private access the
/// Kernel class, by making them friends.
class Table
{
	private:
		friend void isrDispatcher(Arguments& args);

		/// Declare all interrupts service routines with the item trick
		#define ITEM(INDEX) static void isr##INDEX(Arguments& args);
		#include <kernel/item64Helper.itm>
		#undef ITEM

		/// The table of effective ISRs.
		static constexpr void (*_table[idt::idtSize])(Arguments&) =
		{
			/// Assign all 64 ISR table entries with the item trick
			#define ITEM(INDEX) Table::isr##INDEX,
			#include <kernel/item64Helper.itm>
			#undef ITEM
		};
};

Printer& operator<<(Printer& out, const Arguments& args);

} // namespace isr

#endif // ISRDISPATCHER_HPP
