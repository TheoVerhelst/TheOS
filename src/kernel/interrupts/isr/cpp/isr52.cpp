#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr52(isr::IsrArgs /* args */)
{
	out << "Interrupt 52 catched!\n";
	abort();
}
