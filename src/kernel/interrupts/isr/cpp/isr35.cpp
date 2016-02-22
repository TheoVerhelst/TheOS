#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr35(isr::IsrArgs /* args */)
{
	out << "Interrupt 35 catched!\n";
	abort();
}
