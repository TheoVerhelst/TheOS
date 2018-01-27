#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr17(Arguments /* args */)
{
	abort("Interrupt 17 caught!\n");
}

} // namespace isr
