#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr7(Arguments /* args */)
{
	abort("Interrupt 7 caught!\n");
}

} // namespace isr
