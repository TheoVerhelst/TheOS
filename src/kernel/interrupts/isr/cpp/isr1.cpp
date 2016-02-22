#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr1(isr::IsrArgs /* args */)
{
	out << "Interrupt 1 catched!\n";
	abort();
}
