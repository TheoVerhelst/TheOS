#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr28(Arguments /* args */)
{
	abort("Interrupt 28 caught!\n");
}

} // namespace isr
