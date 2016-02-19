#include <Printer.hpp>
#include <kernel/interrupts/isr/isr43.hpp>

void isr43cpp(isr::IsrArgs args)
{
	out << "interrupt 43 catched, aborting\n";
	while(true);
}
