#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr10(Arguments /* args */)
{
	abort("Interrupt 10 caught!\n");
}

} // namespace isr
