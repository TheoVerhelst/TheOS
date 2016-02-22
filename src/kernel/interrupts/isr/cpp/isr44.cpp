#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr44(isr::IsrArgs /* args */)
{
	out << "Interrupt 44 catched!\n";
	abort();
}
