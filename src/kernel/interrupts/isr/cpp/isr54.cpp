#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr54(isr::IsrArgs /* args */)
{
	out << "Interrupt 54 catched!\n";
	abort();
}
