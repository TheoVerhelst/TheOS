#include <Printer.hpp>
#include <kernel/interrupts/isr/isr6.hpp>

void isr6cpp(isr::IsrArgs args)
{
	out << "interrupt 6 catched, aborting\n";
	while(true);
}
