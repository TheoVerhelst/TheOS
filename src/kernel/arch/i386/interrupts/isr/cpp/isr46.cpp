#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr46(Arguments /* args */)
{
	abort("Interrupt 46 caught!\n");
}

} // namespace isr
