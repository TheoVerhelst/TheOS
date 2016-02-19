#include <Printer.hpp>
#include <kernel/interrupts/isr/isr62.hpp>

void isr62cpp(isr::IsrArgs args)
{
	out << "interrupt 62 catched, aborting\n";
	while(true);
}
