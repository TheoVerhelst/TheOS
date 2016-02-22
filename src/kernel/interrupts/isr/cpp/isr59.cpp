#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr59(isr::IsrArgs /* args */)
{
	out << "Interrupt 59 catched!\n";
	abort();
}
