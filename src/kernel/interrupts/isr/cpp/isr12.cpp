#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr12(isr::IsrArgs args)
{
	out << "Interrupt 12 catched!\n";
	abort();
}
