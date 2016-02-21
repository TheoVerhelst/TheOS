#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr27(isr::IsrArgs args)
{
	out << "Interrupt 27 catched!\n";
	abort();
}
