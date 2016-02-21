#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr17(isr::IsrArgs args)
{
	out << "Interrupt 17 catched!\n";
	abort();
}
