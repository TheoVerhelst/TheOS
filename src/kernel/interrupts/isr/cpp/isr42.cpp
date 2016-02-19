#include <Printer.hpp>
#include <kernel/interrupts/isr/isr42.hpp>

void isr42cpp(isr::IsrArgs args)
{
	out << "interrupt 42 catched, aborting\n";
	while(true);
}
