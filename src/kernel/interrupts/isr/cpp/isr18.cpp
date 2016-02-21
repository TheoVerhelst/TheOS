#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr18(isr::IsrArgs args)
{
	out << "Interrupt 18 catched!\n";
	abort();
}
