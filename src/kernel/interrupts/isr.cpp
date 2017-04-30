#include <cpp/Printer.hpp>
#include <kernel/interrupts/pic.hpp>
#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

constexpr void (*Table::_table[idt::idtSize])(Arguments);

extern "C" void isrDispatcher(Arguments args)
{
	// Call the proper ISR
	Table::_table[args._interruptNumber](args);

	// If the interrupt is a mapped IRQ, then send a EOI command to the PIC
	if(args._interruptNumber >= pic::masterOffset and args._interruptNumber <= pic::slaveOffset + 8)
		pic::sendEndOfInterrupt(args._interruptNumber);
}

Printer& operator<<(Printer& out, const ErrorCode& errorCode)
{
	out << errorCode._segmentSelectorIndex << " (";
	out << (errorCode._externalEvent ? "external" : "internal") << ", ";
	if(errorCode._descriptorLocation)
		out << "IDT";
	else
		out << (errorCode._gdtLdt ? "LDT" : "GDT");
	out << ")";
	return out;
}

}// namespace isr
