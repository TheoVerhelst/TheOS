#include <Printer.hpp>
#include <kernel/interrupts/isr/isr7.hpp>

void isr7cpp(isr::IsrArgs args)
{
	out << "interrupt 7 catched, aborting\n";
	while(true);
}
