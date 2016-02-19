#include <Printer.hpp>
#include <kernel/interrupts/isr/isr8.hpp>

void isr8cpp(isr::IsrArgs args)
{
	out << "interrupt 8 catched, aborting\n";
	while(true);
}
