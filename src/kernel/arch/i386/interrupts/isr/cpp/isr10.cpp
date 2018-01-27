#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr10(Arguments /* args */)
{
	abort("Interrupt 10 caught!\n");
}

} // namespace isr
