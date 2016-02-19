#include <Printer.hpp>
#include <kernel/interrupts/isr/isr48.hpp>

void isr48cpp(isr::IsrArgs args)
{
	out << "interrupt 48 catched, aborting\n";
	while(true);
}
