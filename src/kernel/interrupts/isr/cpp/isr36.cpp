#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr36(Arguments /* args */)
{
	abort("Interrupt 36 caught!\n");
}

} // namespace isr
