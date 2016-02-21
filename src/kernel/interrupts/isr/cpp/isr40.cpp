#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr40(isr::IsrArgs args)
{
	out << "Interrupt 40 catched!\n";
	abort();
}
