#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr10(isr::IsrArgs /* args */)
{
	out << "Interrupt 10 catched!\n";
	abort();
}
