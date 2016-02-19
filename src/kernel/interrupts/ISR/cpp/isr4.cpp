#include <Printer.hpp>
#include <kernel/interrupts/isr/isr4.hpp>

void isr4cpp(isr::IsrArgs args)
{
	out << "interrupt 4 catched, aborting\n";
	while(true);
}
