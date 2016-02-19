#include <Printer.hpp>
#include <kernel/interrupts/isr/isr29.hpp>

void isr29cpp(isr::IsrArgs args)
{
	out << "interrupt 29 catched, aborting\n";
	while(true);
}
