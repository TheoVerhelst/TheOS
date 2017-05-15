#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr55(Arguments /* args */)
{
	abort("Interrupt 55 caught!\n");
}

} // namespace isr
