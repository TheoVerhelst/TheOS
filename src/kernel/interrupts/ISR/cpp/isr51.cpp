#include <Printer.hpp>
#include <kernel/interrupts/isr/isr51.hpp>

void isr51cpp(isr::IsrArgs args)
{
	out << "interrupt 51 catched, aborting\n";
	while(true);
}
