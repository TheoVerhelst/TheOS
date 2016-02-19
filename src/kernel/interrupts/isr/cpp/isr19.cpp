#include <Printer.hpp>
#include <kernel/interrupts/isr/isr19.hpp>

void isr19cpp(isr::IsrArgs args)
{
	out << "interrupt 19 catched, aborting\n";
	while(true);
}
