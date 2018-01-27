#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr47(Arguments /* args */)
{
	abort("Interrupt 47 caught!\n");
}

} // namespace isr
