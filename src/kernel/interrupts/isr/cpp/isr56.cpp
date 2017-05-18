#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr56(Arguments /* args */)
{
	abort("Interrupt 56 caught!\n");
}

} // namespace isr
