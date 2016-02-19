#include <Printer.hpp>
#include <kernel/interrupts/isr/isr46.hpp>

void isr46cpp(isr::IsrArgs args)
{
	out << "interrupt 46 catched, aborting\n";
	while(true);
}
