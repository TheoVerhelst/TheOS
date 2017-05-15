#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr59(Arguments /* args */)
{
	abort("Interrupt 59 caught!\n");
}

} // namespace isr
