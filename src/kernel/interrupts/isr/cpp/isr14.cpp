#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr14(Arguments /* args */)
{
	abort("Interrupt 14 caught!\n");
}

} // namespace isr
