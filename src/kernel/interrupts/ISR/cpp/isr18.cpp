#include <Printer.hpp>
#include <kernel/interrupts/isr/isr18.hpp>

void isr18cpp(isr::IsrArgs args)
{
	out << "interrupt 18 catched, aborting\n";
	while(true);
}
