#include <Printer.hpp>
#include <kernel/interrupts/isr/isr47.hpp>

void isr47cpp(isr::IsrArgs args)
{
	out << "interrupt 47 catched, aborting\n";
	while(true);
}
