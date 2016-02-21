#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr47(isr::IsrArgs args)
{
	out << "Interrupt 47 catched!\n";
	abort();
}
