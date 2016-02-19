#include <Printer.hpp>
#include <kernel/interrupts/isr/isr40.hpp>

void isr40cpp(isr::IsrArgs args)
{
	out << "interrupt 40 catched, aborting\n";
	while(true);
}
