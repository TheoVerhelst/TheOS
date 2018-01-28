#include <cpp/Printer.hpp>
#include <kernel/arch/i386/interrupts/pic.hpp>
#include <kernel/arch/i386/interrupts/idt.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

constexpr void (*Table::_table[idt::idtSize])(Arguments&);

extern "C" void isrDispatcher(Arguments& args)
{
	// Call the proper ISR
	Table::_table[args.interruptNumber](args);

	// If the interrupt is a mapped IRQ, then send a EOI command to the PIC
	if(args.interruptNumber >= pic::masterOffset and args.interruptNumber <= pic::slaveOffset + 8)
		pic::sendEndOfInterrupt(args.interruptNumber);
}

void enableInterrupts()
{
	asm volatile("sti");
}

Printer& operator<<(Printer& out, const Arguments& args)
{
	out << Printer::Flags::Hex
		<< "\nEDI: " << args.edi
		<< "\nESI: " << args.esi
		<< "\nEBP: " << args.ebp
		<< "\nESP: " << args.esp
		<< "\nEBX: " << args.ebx
		<< "\nEDX: " << args.edx
		<< "\nECX: " << args.ecx
		<< "\nEAX: " << args.eax
		<< "\nEIP: " << args.eip
		<< "\nCS : " << args.cs
		<< "\nEFLAGS: " << args.eflags
		<< "\ninterrupt number: " << args.interruptNumber
		<< "\nerror code: " << args.errorCode.indexAndFlags;
	return out;
}

} // namespace isr
