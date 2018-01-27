#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr24(Arguments /* args */)
{
	abort("Interrupt 24 caught!\n");
}

} // namespace isr
