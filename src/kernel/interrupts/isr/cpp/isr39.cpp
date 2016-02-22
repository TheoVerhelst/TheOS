#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr39(isr::IsrArgs /* args */)
{
	out << "Interrupt 39 catched!\n";
	abort();
}
