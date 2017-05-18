#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr39(Arguments /* args */)
{
	abort("Interrupt 39 caught!\n");
}

} // namespace isr
