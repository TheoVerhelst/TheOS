#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr60(Arguments /* args */)
{
	abort("Interrupt 60 caught!\n");
}

} // namespace isr
