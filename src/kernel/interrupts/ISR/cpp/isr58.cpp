#include <Printer.hpp>
#include <kernel/interrupts/isr/isr58.hpp>

void isr58cpp(isr::IsrArgs args)
{
	out << "interrupt 58 catched, aborting\n";
	while(true);
}
