#include <Printer.hpp>
#include <kernel/interrupts/isr/isr54.hpp>

void isr54cpp(isr::IsrArgs args)
{
	out << "interrupt 54 catched, aborting\n";
	while(true);
}
