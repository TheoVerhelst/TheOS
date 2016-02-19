#include <Printer.hpp>
#include <kernel/interrupts/isr/isr50.hpp>

void isr50cpp(isr::IsrArgs args)
{
	out << "interrupt 50 catched, aborting\n";
	while(true);
}
