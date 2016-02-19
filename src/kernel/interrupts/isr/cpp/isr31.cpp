#include <Printer.hpp>
#include <kernel/interrupts/isr/isr31.hpp>

void isr31cpp(isr::IsrArgs args)
{
	out << "interrupt 31 catched, aborting\n";
	while(true);
}
