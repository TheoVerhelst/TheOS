#include <Printer.hpp>
#include <kernel/interrupts/isr/isr1.hpp>

void isr1cpp(isr::IsrArgs args)
{
	out << "interrupt 1 catched, aborting\n";
	while(true);
}
