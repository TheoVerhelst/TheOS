#include <Printer.hpp>
#include <kernel/interrupts/isrDispatcher.hpp>
#include <kernel/interrupts/PIC.hpp>

extern "C" void isrDispatcher(uint32_t gs, uint32_t fs, uint32_t es,
		uint32_t ds, uint32_t interruptNumber, ErrorCode errorCode, uint32_t eip,
		uint32_t cs, uint32_t eflags, uint32_t useresp, uint32_t ss)
{
	out << "Interrupt number " << interruptNumber << " caught (error code "
			<< errorCode.segmentSelectorIndex << ", gdtLdt = "
			<< errorCode.gdtLdt << ", descLoc = "
			<< errorCode.descriptorLocation << ").\n";
	// If the interrupt is a mapped IRQ, then send a EOI command to PIC
	if(interruptNumber > pic::masterOffset and interruptNumber < pic::slaveOffset + 8)
		pic::sendEndOfInterrupt(interruptNumber);
	if(interruptNumber == 32 or interruptNumber == 33 or interruptNumber == 13)
	{
		// Wait before next interrupt
		for(int i{0}; i < 10000000; ++i);
		return;
	}
	while(true);
}
