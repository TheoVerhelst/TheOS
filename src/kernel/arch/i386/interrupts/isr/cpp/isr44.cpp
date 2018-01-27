#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr44(Arguments /* args */)
{
	abort("Interrupt 44 caught!\n");
}

} // namespace isr
