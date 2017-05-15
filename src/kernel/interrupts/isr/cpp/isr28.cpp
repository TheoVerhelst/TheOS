#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr28(Arguments /* args */)
{
	abort("Interrupt 28 caught!\n");
}

} // namespace isr
