#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr11(isr::IsrArgs /* args */)
{
	out << "Interrupt 11 catched!\n";
	abort();
}
