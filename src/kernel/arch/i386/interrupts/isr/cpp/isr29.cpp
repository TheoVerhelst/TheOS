#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr29(Arguments /* args */)
{
	abort("Interrupt 29 caught!\n");
}

} // namespace isr
