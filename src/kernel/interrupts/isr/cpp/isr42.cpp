#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr42(Arguments /* args */)
{
	abort("Interrupt 42 caught!\n");
}

} // namespace isr
