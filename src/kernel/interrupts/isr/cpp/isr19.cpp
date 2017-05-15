#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr19(Arguments /* args */)
{
	abort("Interrupt 19 caught!\n");
}

} // namespace isr
