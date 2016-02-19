#include <Printer.hpp>
#include <kernel/interrupts/isr/isr21.hpp>

void isr21cpp(isr::IsrArgs args)
{
	out << "interrupt 21 catched, aborting\n";
	while(true);
}
