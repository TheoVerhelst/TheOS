#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr38(isr::IsrArgs /* args */)
{
	out << "Interrupt 38 catched!\n";
	abort();
}
