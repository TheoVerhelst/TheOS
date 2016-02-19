#include <Printer.hpp>
#include <kernel/interrupts/isr/isr14.hpp>

void isr14cpp(isr::IsrArgs args)
{
	out << "interrupt 14 catched, aborting\n";
	while(true);
}
