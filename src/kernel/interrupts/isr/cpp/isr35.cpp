#include <Printer.hpp>
#include <kernel/interrupts/isr/isr35.hpp>

void isr35cpp(isr::IsrArgs args)
{
	out << "interrupt 35 catched, aborting\n";
	while(true);
}
