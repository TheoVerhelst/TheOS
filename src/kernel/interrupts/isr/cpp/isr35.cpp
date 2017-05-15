#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr35(Arguments /* args */)
{
	abort("Interrupt 35 caught!\n");
}

} // namespace isr
