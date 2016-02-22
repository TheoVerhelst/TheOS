#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr16(isr::IsrArgs /* args */)
{
	out << "Interrupt 16 catched!\n";
	abort();
}
