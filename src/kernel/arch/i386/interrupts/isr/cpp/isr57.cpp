#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr57(Arguments /* args */)
{
	abort("Interrupt 57 caught!\n");
}

} // namespace isr
