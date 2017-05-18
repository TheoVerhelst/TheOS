#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr34(Arguments /* args */)
{
	abort("Interrupt 34 caught!\n");
}

} // namespace isr
