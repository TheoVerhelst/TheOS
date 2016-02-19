#include <Printer.hpp>
#include <kernel/interrupts/isr/isr61.hpp>

void isr61cpp(isr::IsrArgs args)
{
	out << "interrupt 61 catched, aborting\n";
	while(true);
}
