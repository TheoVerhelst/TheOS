#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr26(Arguments /* args */)
{
	abort("Interrupt 26 caught!\n");
}

} // namespace isr
