#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr57(isr::IsrArgs /* args */)
{
	out << "Interrupt 57 catched!\n";
	abort();
}
