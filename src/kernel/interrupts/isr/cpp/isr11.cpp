#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr11(Arguments /* args */)
{
	abort("Interrupt 11 caught!\n");
}

} // namespace isr
