#include <cpp/Printer.hpp>
#include <kernel/arch/i386/interrupts/pic.hpp>
#include <kernel/arch/i386/interrupts/idt.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

constexpr void (*Table::_table[idt::idtSize])(Arguments);

extern "C" void isrDispatcher(Arguments args)
{
	// Call the proper ISR
	Table::_table[args.interruptNumber](args);

	// If the interrupt is a mapped IRQ, then send a EOI command to the PIC
	if(args.interruptNumber >= pic::masterOffset and args.interruptNumber <= pic::slaveOffset + 8)
		pic::sendEndOfInterrupt(args.interruptNumber);
}

Printer& operator<<(Printer& out, const ErrorCode& errorCode)
{
	out << (errorCode.indexAndFlags & Flags::ExternalEvent ? "external" : "internal") << " at ";
	out << (errorCode.indexAndFlags & Flags::DescriptorLocation ? "idt" : (errorCode.indexAndFlags & Flags::GdtLdt ? "ldt" : "gdt"));
	out << "[" << ((errorCode.indexAndFlags & 0xFFF8) >> 3) << "]";
	return out;
}

} // namespace isr
