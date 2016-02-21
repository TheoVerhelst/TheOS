#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr55(isr::IsrArgs args)
{
	out << "Interrupt 55 catched!\n";
	abort();
}
