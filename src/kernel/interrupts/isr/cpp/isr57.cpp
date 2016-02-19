#include <Printer.hpp>
#include <kernel/interrupts/isr/isr57.hpp>

void isr57cpp(isr::IsrArgs args)
{
	out << "interrupt 57 catched, aborting\n";
	while(true);
}
