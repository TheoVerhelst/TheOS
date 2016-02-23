#include <Printer.hpp>
#include <kernel/interrupts/pic.hpp>
#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/isr.hpp>

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
	out << errorCode.segmentSelectorIndex << " (";
	out << (errorCode.externalEvent ? "external" : "internal") << ", ";
	if(errorCode.descriptorLocation)
		out << "IDT";
	else
		out << (errorCode.gdtLdt ? "LDT" : "GDT");
	out << ")";
	return out;
}

}// namespace isr
