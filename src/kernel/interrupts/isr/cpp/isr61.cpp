#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr61(isr::IsrArgs /* args */)
{
	out << "Interrupt 61 catched!\n";
	abort();
}
