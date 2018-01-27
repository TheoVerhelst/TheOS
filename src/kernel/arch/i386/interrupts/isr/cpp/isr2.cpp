#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr2(Arguments /* args */)
{
	abort("Interrupt 2 caught!\n");
}

} // namespace isr
