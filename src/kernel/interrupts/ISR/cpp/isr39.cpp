#include <Printer.hpp>
#include <kernel/interrupts/isr/isr39.hpp>

void isr39cpp(isr::IsrArgs args)
{
	out << "interrupt 39 catched, aborting\n";
	while(true);
}
