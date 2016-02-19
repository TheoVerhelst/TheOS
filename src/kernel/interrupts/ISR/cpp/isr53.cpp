#include <Printer.hpp>
#include <kernel/interrupts/isr/isr53.hpp>

void isr53cpp(isr::IsrArgs args)
{
	out << "interrupt 53 catched, aborting\n";
	while(true);
}
