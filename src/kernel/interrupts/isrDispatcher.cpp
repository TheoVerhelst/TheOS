#include <Printer.hpp>
#include <kernel/interrupts/isrDispatcher.hpp>
#include <kernel/interrupts/PIC.hpp>
#include <kernel/interrupts/IDT.hpp>

Printer& operator<<(Printer& out, const ErrorCode& errorCode)
{
	out << errorCode.segmentSelectorIndex << "(";
	out << (errorCode.externalEvent ? "external" : "internal") << ", ";
	if(errorCode.descriptorLocation)
		out << "IDT";
	else
		out << (errorCode.gdtLdt ? "LDT" : "GDT");
	out << ")";
	return out;
}

extern "C" void isrDispatcher(uint32_t gs, uint32_t fs, uint32_t es,
		uint32_t ds, uint32_t interruptNumber, ErrorCode errorCode, uint32_t eip,
		uint32_t cs, uint32_t eflags, uint32_t useresp, uint32_t ss)
{
	// Log the interrupt
	out << "Interrupt number " << interruptNumber << ", error code " << errorCode << ".\n";

	// If the interrupt is a mapped IRQ, then send a EOI command to PIC
	if(interruptNumber > pic::masterOffset and interruptNumber < pic::slaveOffset + 8)
		pic::sendEndOfInterrupt(interruptNumber);

	// Return from interrupt if possible
	if(interruptNumber == idt::Interrupt::Timer
			or interruptNumber == idt::Interrupt::Keyboard
			or interruptNumber == idt::Interrupt::GeneralProtection)
		return;
	while(true);
}
