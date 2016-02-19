#include <Printer.hpp>
#include <kernel/interrupts/isr/isr34.hpp>

void isr34cpp(isr::IsrArgs args)
{
	out << "interrupt 34 catched, aborting\n";
	while(true);
}
