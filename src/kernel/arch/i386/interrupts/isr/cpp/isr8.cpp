#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr8(Arguments /* args */)
{
	abort("Interrupt 8 caught!\n");
}

} // namespace isr
