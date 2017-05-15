#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr12(Arguments /* args */)
{
	abort("Interrupt 12 caught!\n");
}

} // namespace isr
