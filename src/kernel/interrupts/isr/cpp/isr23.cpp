#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr23(Arguments /* args */)
{
	abort("Interrupt 23 caught!\n");
}

} // namespace isr
