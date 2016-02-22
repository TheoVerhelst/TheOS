#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr60(isr::IsrArgs /* args */)
{
	out << "Interrupt 60 catched!\n";
	abort();
}
