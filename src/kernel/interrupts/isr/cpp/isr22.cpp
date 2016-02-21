#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr22(isr::IsrArgs args)
{
	out << "Interrupt 22 catched!\n";
	abort();
}
