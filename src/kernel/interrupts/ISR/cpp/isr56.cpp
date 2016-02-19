#include <Printer.hpp>
#include <kernel/interrupts/isr/isr56.hpp>

void isr56cpp(isr::IsrArgs args)
{
	out << "interrupt 56 catched, aborting\n";
	while(true);
}
