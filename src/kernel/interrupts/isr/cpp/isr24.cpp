#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr24(isr::IsrArgs args)
{
	out << "Interrupt 24 catched!\n";
	abort();
}
