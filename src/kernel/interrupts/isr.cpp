#include <Printer.hpp>
#include <kernel/interrupts/isr.hpp>
#include <kernel/interrupts/pic.hpp>
#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/isr/isr0.hpp>
#include <kernel/interrupts/isr/isr1.hpp>
#include <kernel/interrupts/isr/isr2.hpp>
#include <kernel/interrupts/isr/isr3.hpp>
#include <kernel/interrupts/isr/isr4.hpp>
#include <kernel/interrupts/isr/isr5.hpp>
#include <kernel/interrupts/isr/isr6.hpp>
#include <kernel/interrupts/isr/isr7.hpp>
#include <kernel/interrupts/isr/isr8.hpp>
#include <kernel/interrupts/isr/isr9.hpp>
#include <kernel/interrupts/isr/isr10.hpp>
#include <kernel/interrupts/isr/isr11.hpp>
#include <kernel/interrupts/isr/isr12.hpp>
#include <kernel/interrupts/isr/isr13.hpp>
#include <kernel/interrupts/isr/isr14.hpp>
#include <kernel/interrupts/isr/isr15.hpp>
#include <kernel/interrupts/isr/isr16.hpp>
#include <kernel/interrupts/isr/isr17.hpp>
#include <kernel/interrupts/isr/isr18.hpp>
#include <kernel/interrupts/isr/isr19.hpp>
#include <kernel/interrupts/isr/isr20.hpp>
#include <kernel/interrupts/isr/isr21.hpp>
#include <kernel/interrupts/isr/isr22.hpp>
#include <kernel/interrupts/isr/isr23.hpp>
#include <kernel/interrupts/isr/isr24.hpp>
#include <kernel/interrupts/isr/isr25.hpp>
#include <kernel/interrupts/isr/isr26.hpp>
#include <kernel/interrupts/isr/isr27.hpp>
#include <kernel/interrupts/isr/isr28.hpp>
#include <kernel/interrupts/isr/isr29.hpp>
#include <kernel/interrupts/isr/isr30.hpp>
#include <kernel/interrupts/isr/isr31.hpp>
#include <kernel/interrupts/isr/isr32.hpp>
#include <kernel/interrupts/isr/isr33.hpp>
#include <kernel/interrupts/isr/isr34.hpp>
#include <kernel/interrupts/isr/isr35.hpp>
#include <kernel/interrupts/isr/isr36.hpp>
#include <kernel/interrupts/isr/isr37.hpp>
#include <kernel/interrupts/isr/isr38.hpp>
#include <kernel/interrupts/isr/isr39.hpp>
#include <kernel/interrupts/isr/isr40.hpp>
#include <kernel/interrupts/isr/isr41.hpp>
#include <kernel/interrupts/isr/isr42.hpp>
#include <kernel/interrupts/isr/isr43.hpp>
#include <kernel/interrupts/isr/isr44.hpp>
#include <kernel/interrupts/isr/isr45.hpp>
#include <kernel/interrupts/isr/isr46.hpp>
#include <kernel/interrupts/isr/isr47.hpp>
#include <kernel/interrupts/isr/isr48.hpp>
#include <kernel/interrupts/isr/isr49.hpp>
#include <kernel/interrupts/isr/isr50.hpp>
#include <kernel/interrupts/isr/isr51.hpp>
#include <kernel/interrupts/isr/isr52.hpp>
#include <kernel/interrupts/isr/isr53.hpp>
#include <kernel/interrupts/isr/isr54.hpp>
#include <kernel/interrupts/isr/isr55.hpp>
#include <kernel/interrupts/isr/isr56.hpp>
#include <kernel/interrupts/isr/isr57.hpp>
#include <kernel/interrupts/isr/isr58.hpp>
#include <kernel/interrupts/isr/isr59.hpp>
#include <kernel/interrupts/isr/isr60.hpp>
#include <kernel/interrupts/isr/isr61.hpp>
#include <kernel/interrupts/isr/isr62.hpp>
#include <kernel/interrupts/isr/isr63.hpp>

namespace isr
{

// Assign all 64 ISR table entries with the item trick
void (*isrTable[idt::idtSize])(IsrArgs) = {
#define ITEM(INDEX) isr##INDEX##cpp,
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
	// Log the interrupt
	out << "Interrupt number " << args.interruptNumber << ", error code " << args.errorCode << "\n";

	// If the interrupt is a mapped IRQ, then send a EOI command to PIC
	if(args.interruptNumber >= pic::masterOffset and args.interruptNumber <= pic::slaveOffset + 8)
		pic::sendEndOfInterrupt(args.interruptNumber);

	// Call the proper ISR
	isr::isrTable[args.interruptNumber](args);
}
