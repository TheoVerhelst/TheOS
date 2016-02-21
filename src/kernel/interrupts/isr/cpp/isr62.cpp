#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr62(isr::IsrArgs args)
{
	out << "Interrupt 62 catched!\n";
	abort();
}
