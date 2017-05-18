#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr50(Arguments /* args */)
{
	abort("Interrupt 50 caught!\n");
}

} // namespace isr
