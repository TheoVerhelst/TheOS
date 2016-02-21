#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr46(isr::IsrArgs args)
{
	out << "Interrupt 46 catched!\n";
	abort();
}
