#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr15(isr::IsrArgs /* args */)
{
	out << "Interrupt 15 catched!\n";
	abort();
}
