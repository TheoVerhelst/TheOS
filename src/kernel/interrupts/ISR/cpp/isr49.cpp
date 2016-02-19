#include <Printer.hpp>
#include <kernel/interrupts/isr/isr49.hpp>

void isr49cpp(isr::IsrArgs args)
{
	out << "interrupt 49 catched, aborting\n";
	while(true);
}
