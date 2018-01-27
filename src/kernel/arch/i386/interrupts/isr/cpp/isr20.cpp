#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr20(Arguments /* args */)
{
	abort("Interrupt 20 caught!\n");
}

} // namespace isr
