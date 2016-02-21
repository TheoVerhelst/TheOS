#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr31(isr::IsrArgs args)
{
	out << "Interrupt 31 catched!\n";
	abort();
}
