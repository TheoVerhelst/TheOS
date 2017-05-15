#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr45(Arguments /* args */)
{
	abort("Interrupt 45 caught!\n");
}

} // namespace isr
