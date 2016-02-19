#include <Printer.hpp>
#include <kernel/interrupts/isr/isr16.hpp>

void isr16cpp(isr::IsrArgs args)
{
	out << "interrupt 16 catched, aborting\n";
	while(true);
}
