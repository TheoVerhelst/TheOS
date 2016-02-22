#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr28(isr::IsrArgs /* args */)
{
	out << "Interrupt 28 catched!\n";
	abort();
}
