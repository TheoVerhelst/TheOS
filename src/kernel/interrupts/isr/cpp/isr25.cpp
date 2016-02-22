#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr25(isr::IsrArgs /* args */)
{
	out << "Interrupt 25 catched!\n";
	abort();
}
