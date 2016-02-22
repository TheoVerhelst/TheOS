#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr26(isr::IsrArgs /* args */)
{
	out << "Interrupt 26 catched!\n";
	abort();
}
