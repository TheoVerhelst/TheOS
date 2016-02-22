#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr9(isr::IsrArgs /* args */)
{
	out << "Interrupt 9 catched!\n";
	abort();
}
