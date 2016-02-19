#include <Printer.hpp>
#include <kernel/interrupts/isr/isr2.hpp>

void isr2cpp(isr::IsrArgs args)
{
	out << "interrupt 2 catched, aborting\n";
	while(true);
}
