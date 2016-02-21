#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr8(isr::IsrArgs args)
{
	out << "Interrupt 8 catched!\n";
	abort();
}
