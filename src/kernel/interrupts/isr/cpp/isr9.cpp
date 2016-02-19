#include <Printer.hpp>
#include <kernel/interrupts/isr/isr9.hpp>

void isr9cpp(isr::IsrArgs args)
{
	out << "interrupt 9 catched, aborting\n";
	while(true);
}
