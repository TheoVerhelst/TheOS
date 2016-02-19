#include <Printer.hpp>
#include <kernel/interrupts/isr/isr27.hpp>

void isr27cpp(isr::IsrArgs args)
{
	out << "interrupt 27 catched, aborting\n";
	while(true);
}
