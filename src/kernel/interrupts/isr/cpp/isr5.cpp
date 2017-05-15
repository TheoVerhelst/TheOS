#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr5(Arguments /* args */)
{
	abort("Interrupt 5 caught!\n");
}

} // namespace isr
