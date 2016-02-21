#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr6(isr::IsrArgs args)
{
	out << "Interrupt 6 catched!\n";
	abort();
}
