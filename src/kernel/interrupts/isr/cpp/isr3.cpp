#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr3(isr::IsrArgs /* args */)
{
	out << "Interrupt 3 catched!\n";
	abort();
}
