#include <Printer.hpp>
#include <kernel/interrupts/isr/isr38.hpp>

void isr38cpp(isr::IsrArgs args)
{
	out << "interrupt 38 catched, aborting\n";
	while(true);
}
