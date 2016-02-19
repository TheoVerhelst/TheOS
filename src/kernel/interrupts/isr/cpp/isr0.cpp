#include <Printer.hpp>
#include <kernel/interrupts/isr/isr0.hpp>

void isr0cpp(isr::IsrArgs args)
{
	out << "interrupt 0 catched, aborting\n";
	while(true);
}
