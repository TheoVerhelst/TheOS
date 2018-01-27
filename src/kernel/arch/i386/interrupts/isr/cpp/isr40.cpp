#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr40(Arguments /* args */)
{
	abort("Interrupt 40 caught!\n");
}

} // namespace isr
