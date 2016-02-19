#include <Printer.hpp>
#include <kernel/interrupts/isr/isr60.hpp>

void isr60cpp(isr::IsrArgs args)
{
	out << "interrupt 60 catched, aborting\n";
	while(true);
}
