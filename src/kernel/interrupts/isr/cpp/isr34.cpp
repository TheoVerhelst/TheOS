#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr34(isr::IsrArgs args)
{
	out << "Interrupt 34 catched!\n";
	abort();
}
