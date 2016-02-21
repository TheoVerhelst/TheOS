#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr7(isr::IsrArgs args)
{
	out << "Interrupt 7 catched!\n";
	abort();
}
