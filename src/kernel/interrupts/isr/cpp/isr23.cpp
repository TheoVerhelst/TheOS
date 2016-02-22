#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr23(isr::IsrArgs /* args */)
{
	out << "Interrupt 23 catched!\n";
	abort();
}
