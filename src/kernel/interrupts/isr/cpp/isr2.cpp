#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr2(isr::IsrArgs args)
{
	out << "Interrupt 2 catched!\n";
	abort();
}
