#include <Printer.hpp>
#include <kernel/interrupts/isr/isr10.hpp>

void isr10cpp(isr::IsrArgs args)
{
	out << "interrupt 10 catched, aborting\n";
	while(true);
}
