#include <Printer.hpp>
#include <kernel/interrupts/isr/isr30.hpp>

void isr30cpp(isr::IsrArgs args)
{
	out << "interrupt 30 catched, aborting\n";
	while(true);
}
