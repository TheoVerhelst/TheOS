#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr49(isr::IsrArgs args)
{
	out << "Interrupt 49 catched!\n";
	abort();
}
