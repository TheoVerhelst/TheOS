#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr18(Arguments /* args */)
{
	abort("Interrupt 18 caught!\n");
}

} // namespace isr
