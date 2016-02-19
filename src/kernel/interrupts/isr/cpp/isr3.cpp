#include <Printer.hpp>
#include <kernel/interrupts/isr/isr3.hpp>

void isr3cpp(isr::IsrArgs args)
{
	out << "interrupt 3 catched, aborting\n";
	while(true);
}
