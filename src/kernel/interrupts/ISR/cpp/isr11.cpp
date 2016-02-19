#include <Printer.hpp>
#include <kernel/interrupts/isr/isr11.hpp>

void isr11cpp(isr::IsrArgs args)
{
	out << "interrupt 11 catched, aborting\n";
	while(true);
}
