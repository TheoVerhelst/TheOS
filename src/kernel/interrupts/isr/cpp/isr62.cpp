#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr62(Arguments /* args */)
{
	abort("Interrupt 62 caught!\n");
}

} // namespace isr
