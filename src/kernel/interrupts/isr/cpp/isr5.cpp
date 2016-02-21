#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr5(isr::IsrArgs args)
{
	out << "Interrupt 5 catched!\n";
	abort();
}
