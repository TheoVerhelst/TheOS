#include <Printer.hpp>
#include <kernel/interrupts/isr/isr24.hpp>

void isr24cpp(isr::IsrArgs args)
{
	out << "interrupt 24 catched, aborting\n";
	while(true);
}
