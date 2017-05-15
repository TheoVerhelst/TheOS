#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr0(Arguments /* args */)
{
	abort("Interrupt 0 caught!\n");
}

} // namespace isr
