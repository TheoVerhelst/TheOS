#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr48(isr::IsrArgs /* args */)
{
	out << "Interrupt 48 catched!\n";
	abort();
}
