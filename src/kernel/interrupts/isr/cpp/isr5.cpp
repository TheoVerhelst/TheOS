#include <Printer.hpp>
#include <kernel/interrupts/isr/isr5.hpp>

void isr5cpp(isr::IsrArgs args)
{
	out << "interrupt 5 catched, aborting\n";
	while(true);
}
