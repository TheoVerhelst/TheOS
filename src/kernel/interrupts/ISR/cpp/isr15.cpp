#include <Printer.hpp>
#include <kernel/interrupts/isr/isr15.hpp>

void isr15cpp(isr::IsrArgs args)
{
	out << "interrupt 15 catched, aborting\n";
	while(true);
}
