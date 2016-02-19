#include <Printer.hpp>
#include <kernel/interrupts/isr/isr20.hpp>

void isr20cpp(isr::IsrArgs args)
{
	out << "interrupt 20 catched, aborting\n";
	while(true);
}
