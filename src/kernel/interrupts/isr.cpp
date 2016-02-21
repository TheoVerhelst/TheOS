#include <Printer.hpp>
#include <kernel/interrupts/pic.hpp>
#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/isr.hpp>
#include <kernel/Kernel.hpp>

namespace isr
{

// Assign all 64 ISR table entries with the item trick
void (Kernel::*isrTable[idt::idtSize])(IsrArgs) = {
#define ITEM(INDEX) &Kernel::isr##INDEX,
#include <kernel/item64Helper.itm>
#undef ITEM
};

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

extern "C" void isrDispatcher(isr::IsrArgs args)
{
	// Call the proper ISR on the kernel
	(kernel.*isr::isrTable[args.interruptNumber])(args);

	// If the interrupt is a mapped IRQ, then send a EOI command to PIC
	if(args.interruptNumber >= pic::masterOffset and args.interruptNumber <= pic::slaveOffset + 8)
		pic::sendEndOfInterrupt(args.interruptNumber);
}
