#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr53(isr::IsrArgs /* args */)
{
	out << "Interrupt 53 catched!\n";
	abort();
}
