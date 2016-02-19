#include <Printer.hpp>
#include <kernel/interrupts/isr/isr26.hpp>

void isr26cpp(isr::IsrArgs args)
{
	out << "interrupt 26 catched, aborting\n";
	while(true);
}
