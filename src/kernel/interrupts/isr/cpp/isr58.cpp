#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr58(isr::IsrArgs /* args */)
{
	out << "Interrupt 58 catched!\n";
	abort();
}
