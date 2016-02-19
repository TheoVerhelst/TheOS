#include <Printer.hpp>
#include <kernel/interrupts/isr/isr59.hpp>

void isr59cpp(isr::IsrArgs args)
{
	out << "interrupt 59 catched, aborting\n";
	while(true);
}
