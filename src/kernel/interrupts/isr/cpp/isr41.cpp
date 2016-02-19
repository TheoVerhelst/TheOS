#include <Printer.hpp>
#include <kernel/interrupts/isr/isr41.hpp>

void isr41cpp(isr::IsrArgs args)
{
	out << "interrupt 41 catched, aborting\n";
	while(true);
}
