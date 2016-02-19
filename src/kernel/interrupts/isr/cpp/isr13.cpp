#include <Printer.hpp>
#include <kernel/interrupts/isr/isr13.hpp>

void isr13cpp(isr::IsrArgs args)
{
	out << "interrupt 13 catched, aborting\n";
	while(true);
}
