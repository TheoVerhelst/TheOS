#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr4(isr::IsrArgs /* args */)
{
	out << "Interrupt 4 catched!\n";
	abort();
}
