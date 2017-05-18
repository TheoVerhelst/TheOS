#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr24(Arguments /* args */)
{
	abort("Interrupt 24 caught!\n");
}

} // namespace isr
