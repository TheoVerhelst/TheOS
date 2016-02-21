#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr50(isr::IsrArgs args)
{
	out << "Interrupt 50 catched!\n";
	abort();
}
