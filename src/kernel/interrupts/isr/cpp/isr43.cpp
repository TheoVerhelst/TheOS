#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr43(Arguments /* args */)
{
	abort("Interrupt 43 caught!\n");
}

} // namespace isr
