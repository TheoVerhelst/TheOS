#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr45(isr::IsrArgs args)
{
	out << "Interrupt 45 catched!\n";
	abort();
}
