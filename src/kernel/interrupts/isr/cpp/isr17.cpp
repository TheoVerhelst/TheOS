#include <Printer.hpp>
#include <kernel/interrupts/isr/isr17.hpp>

void isr17cpp(isr::IsrArgs args)
{
	out << "interrupt 17 catched, aborting\n";
	while(true);
}
