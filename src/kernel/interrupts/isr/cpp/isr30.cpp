#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr30(isr::IsrArgs /* args */)
{
	out << "Interrupt 30 catched!\n";
	abort();
}
