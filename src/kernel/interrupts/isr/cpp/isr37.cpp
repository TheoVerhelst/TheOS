#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr37(isr::IsrArgs args)
{
	out << "Interrupt 37 catched!\n";
	abort();
}
