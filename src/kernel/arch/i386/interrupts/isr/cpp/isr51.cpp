#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr51(Arguments /* args */)
{
	abort("Interrupt 51 caught!\n");
}

} // namespace isr
