#include <Printer.hpp>
#include <kernel/interrupts/isr/isr45.hpp>

void isr45cpp(isr::IsrArgs args)
{
	out << "interrupt 45 catched, aborting\n";
	while(true);
}
