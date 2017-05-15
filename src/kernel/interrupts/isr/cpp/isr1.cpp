#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr1(Arguments /* args */)
{
	abort("Interrupt 1 caught!\n");
}

} // namespace isr
