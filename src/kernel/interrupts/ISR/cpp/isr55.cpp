#include <Printer.hpp>
#include <kernel/interrupts/isr/isr55.hpp>

void isr55cpp(isr::IsrArgs args)
{
	out << "interrupt 55 catched, aborting\n";
	while(true);
}
