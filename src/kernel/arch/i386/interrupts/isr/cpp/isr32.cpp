#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr32(Arguments /* args */)
{
	abort("Interrupt 32 caught!\n");
}

} // namespace isr
