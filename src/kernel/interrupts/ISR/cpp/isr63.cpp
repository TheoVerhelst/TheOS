#include <Printer.hpp>
#include <kernel/interrupts/isr/isr63.hpp>

void isr63cpp(isr::IsrArgs args)
{
	out << "interrupt 63 catched, aborting\n";
	while(true);
}
