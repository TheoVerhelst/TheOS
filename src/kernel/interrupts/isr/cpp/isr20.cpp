#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr20(isr::IsrArgs /* args */)
{
	out << "Interrupt 20 catched!\n";
	abort();
}
