#include <Printer.hpp>
#include <kernel/interrupts/isr/isr37.hpp>

void isr37cpp(isr::IsrArgs args)
{
	out << "interrupt 37 catched, aborting\n";
	while(true);
}
