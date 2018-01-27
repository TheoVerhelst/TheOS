#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr15(Arguments /* args */)
{
	abort("Interrupt 15 caught!\n");
}

} // namespace isr
