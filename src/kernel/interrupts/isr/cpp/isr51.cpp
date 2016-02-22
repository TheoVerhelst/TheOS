#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr51(isr::IsrArgs /* args */)
{
	out << "Interrupt 51 catched!\n";
	abort();
}
