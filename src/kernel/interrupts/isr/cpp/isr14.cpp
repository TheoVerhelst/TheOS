#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr14(isr::IsrArgs args)
{
	out << "Interrupt 14 catched!\n";
	abort();
}
