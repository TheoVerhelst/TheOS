#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr5(Arguments /* args */)
{
	abort("Interrupt 5 caught!\n");
}

} // namespace isr
