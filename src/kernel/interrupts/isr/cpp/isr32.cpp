#include <Printer.hpp>
#include <kernel/interrupts/isr/isr32.hpp>

void isr32cpp(isr::IsrArgs args)
{
	out << "interrupt 32 catched, aborting\n";
	while(true);
}
