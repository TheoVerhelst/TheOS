#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr7(Arguments /* args */)
{
	abort("Interrupt 7 caught!\n");
}

} // namespace isr
