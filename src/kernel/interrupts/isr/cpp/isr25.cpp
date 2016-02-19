#include <Printer.hpp>
#include <kernel/interrupts/isr/isr25.hpp>

void isr25cpp(isr::IsrArgs args)
{
	out << "interrupt 25 catched, aborting\n";
	while(true);
}
