#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr36(isr::IsrArgs /* args */)
{
	out << "Interrupt 36 catched!\n";
	abort();
}
