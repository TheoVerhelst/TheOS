#include <Printer.hpp>
#include <kernel/Kernel.hpp>

void Kernel::isr41(isr::IsrArgs /* args */)
{
	out << "Interrupt 41 catched!\n";
	abort();
}
