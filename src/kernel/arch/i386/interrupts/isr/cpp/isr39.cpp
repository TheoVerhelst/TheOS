#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr39(Arguments /* args */)
{
	abort("Interrupt 39 caught!\n");
}

} // namespace isr
