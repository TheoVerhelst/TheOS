#ifndef ISRDISPATCHER_HPP
#define ISRDISPATCHER_HPP

#include <cstdint>
#include <Printer.hpp>
#include <kernel/interrupts/idt.hpp>

namespace isr
{

/// When an exception condition is related to a specific segment selector or IDT
/// vector, the processor pushes an error code onto the stack of the exception
/// handler (whether it is a procedure or task). The error code resembles a
/// segment selector; however, instead of a TI flag and RPL field, the error
/// code contains 3 flags:
struct ErrorCode
{
	/// When set, indicates that the exception occurred during delivery of an
	/// event external to the program, such as an interrupt or an earlier exception.
	uint8_t externalEvent:1;

	/// When set, indicates that the index portion of the error code refers
	/// to a gate descriptor in the IDT; when clear, indicates that the index
	/// refers to a descriptor in the GDT or the current LDT.
	uint8_t descriptorLocation:1;

	/// Only used when the IDT flag is clear. When set, the TI flag indicates
	/// that the index portion of the error code refers to a segment or gate
	/// descriptor in the LDT; when clear, it indicates that the index refers to
	/// a descriptor in the current GDT.
	uint8_t gdtLdt:1;

	/// provides an index into the IDT, GDT, or current LDT to the segment or
	/// gate selector being referenced by the error code.
	uint16_t segmentSelectorIndex:13;

	uint16_t reserved;
} __attribute__((packed));
static_assert(sizeof(ErrorCode) == 4, "Error code structure must be 32-bit");

struct Arguments
{
	uint32_t gs;
	uint32_t fs;
	uint32_t es;
	uint32_t ds;
	uint32_t interruptNumber;
	ErrorCode errorCode;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t useresp;
	uint32_t ss;
};

/// Calls the apropriate C-written ISR, and logs the interrupt if needed.
extern "C" void isrDispatcher(Arguments args);

class Table
{
	private:
		/// Calls the apropriate C-written ISR, and logs the interrupt if needed.
		friend void isrDispatcher(Arguments args);

		// Declare all interrupts service routines with the item trick
#define ITEM(INDEX) static void isr##INDEX(Arguments args);
#include <kernel/item64Helper.itm>
#undef ITEM

		/// The table of effective ISRs.
		static constexpr void (*_table[idt::idtSize])(Arguments) =
		{
// Assign all 64 ISR table entries with the item trick
#define ITEM(INDEX) Table::isr##INDEX,
#include <kernel/item64Helper.itm>
#undef ITEM
		};
};

/// Fancy printing of the error code to \a out.
Printer& operator<<(Printer& out, const ErrorCode& errorCode);

}// namespace isr

#endif// ISRDISPATCHER_HPP
