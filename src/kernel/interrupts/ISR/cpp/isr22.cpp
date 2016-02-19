#include <Printer.hpp>
#include <kernel/interrupts/isr/isr22.hpp>

void isr22cpp(isr::IsrArgs args)
{
	out << "interrupt 22 catched, aborting\n";
	while(true);
}
