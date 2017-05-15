#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr30(Arguments /* args */)
{
	abort("Interrupt 30 caught!\n");
}

} // namespace isr
