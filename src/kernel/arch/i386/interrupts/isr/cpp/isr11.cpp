#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr11(Arguments /* args */)
{
	abort("Interrupt 11 caught!\n");
}

} // namespace isr
