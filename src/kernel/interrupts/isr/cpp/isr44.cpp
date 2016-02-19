#include <Printer.hpp>
#include <kernel/interrupts/isr/isr44.hpp>

void isr44cpp(isr::IsrArgs args)
{
	out << "interrupt 44 catched, aborting\n";
	while(true);
}
