#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr19(isr::IsrArgs /* args */)
{
	out << "Interrupt 19 catched!\n";
	abort();
}
