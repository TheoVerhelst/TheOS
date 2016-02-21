#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr0(isr::IsrArgs args)
{
	out << "Interrupt 0 catched!\n";
	abort();
}
