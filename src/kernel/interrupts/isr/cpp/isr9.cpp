#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr9(Arguments /* args */)
{
	abort("Interrupt 9 caught!\n");
}

} // namespace isr
