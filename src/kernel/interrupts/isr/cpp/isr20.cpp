#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr20(Arguments /* args */)
{
	abort("Interrupt 20 caught!\n");
}

} // namespace isr
