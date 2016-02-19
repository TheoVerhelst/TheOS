#include <Printer.hpp>
#include <kernel/interrupts/isr/isr12.hpp>

void isr12cpp(isr::IsrArgs args)
{
	out << "interrupt 12 catched, aborting\n";
	while(true);
}
