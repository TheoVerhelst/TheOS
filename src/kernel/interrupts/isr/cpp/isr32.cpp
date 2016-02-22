#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr32(isr::IsrArgs /* args */)
{
	out << "Interrupt 32 catched!\n";
	abort();
}
