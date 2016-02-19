#include <Printer.hpp>
#include <kernel/interrupts/isr/isr36.hpp>

void isr36cpp(isr::IsrArgs args)
{
	out << "interrupt 36 catched, aborting\n";
	while(true);
}
