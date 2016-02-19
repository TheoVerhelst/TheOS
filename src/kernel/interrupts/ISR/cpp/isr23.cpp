#include <Printer.hpp>
#include <kernel/interrupts/isr/isr23.hpp>

void isr23cpp(isr::IsrArgs args)
{
	out << "interrupt 23 catched, aborting\n";
	while(true);
}
