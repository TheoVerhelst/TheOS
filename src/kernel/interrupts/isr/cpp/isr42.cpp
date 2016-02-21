#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr42(isr::IsrArgs args)
{
	out << "Interrupt 42 catched!\n";
	abort();
}
