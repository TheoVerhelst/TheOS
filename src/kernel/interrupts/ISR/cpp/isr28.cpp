#include <Printer.hpp>
#include <kernel/interrupts/isr/isr28.hpp>

void isr28cpp(isr::IsrArgs args)
{
	out << "interrupt 28 catched, aborting\n";
	while(true);
}
