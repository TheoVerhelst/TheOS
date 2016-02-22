#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr63(isr::IsrArgs /* args */)
{
	out << "Interrupt 63 catched!\n";
	abort();
}
