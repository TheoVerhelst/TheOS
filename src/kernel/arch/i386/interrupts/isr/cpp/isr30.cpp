#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr30(Arguments /* args */)
{
	abort("Interrupt 30 caught!\n");
}

} // namespace isr
