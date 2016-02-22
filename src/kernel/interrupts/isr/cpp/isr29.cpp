#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr29(isr::IsrArgs /* args */)
{
	out << "Interrupt 29 catched!\n";
	abort();
}
