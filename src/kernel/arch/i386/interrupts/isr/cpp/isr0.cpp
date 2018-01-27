#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr0(Arguments /* args */)
{
	abort("Interrupt 0 caught!\n");
}

} // namespace isr
