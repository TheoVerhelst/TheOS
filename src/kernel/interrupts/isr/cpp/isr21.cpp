#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr21(isr::IsrArgs args)
{
	out << "Interrupt 21 catched!\n";
	abort();
}
