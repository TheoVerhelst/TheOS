#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr13(isr::IsrArgs args)
{
	out << "Interrupt 13 catched!\n";
	abort();
}
