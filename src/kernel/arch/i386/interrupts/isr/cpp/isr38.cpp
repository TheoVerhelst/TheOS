#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr38(Arguments /* args */)
{
	abort("Interrupt 38 caught!\n");
}

} // namespace isr
