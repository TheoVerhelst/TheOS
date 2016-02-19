#include <Printer.hpp>
#include <kernel/interrupts/isr/isr52.hpp>

void isr52cpp(isr::IsrArgs args)
{
	out << "interrupt 52 catched, aborting\n";
	while(true);
}
