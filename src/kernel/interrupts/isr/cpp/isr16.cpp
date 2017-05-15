#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr16(Arguments /* args */)
{
	abort("Interrupt 16 caught!\n");
}

} // namespace isr
