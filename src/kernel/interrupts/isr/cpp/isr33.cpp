#include <Printer.hpp>
#include <kernel/interrupts/isr/isr33.hpp>

void isr33cpp(isr::IsrArgs args)
{
	out << "interrupt 33 catched, aborting\n";
	while(true);
}
