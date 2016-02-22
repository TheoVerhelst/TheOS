#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr56(isr::IsrArgs /* args */)
{
	out << "Interrupt 56 catched!\n";
	abort();
}
