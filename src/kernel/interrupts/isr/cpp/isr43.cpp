#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr43(isr::IsrArgs args)
{
	out << "Interrupt 43 catched!\n";
	abort();
}
