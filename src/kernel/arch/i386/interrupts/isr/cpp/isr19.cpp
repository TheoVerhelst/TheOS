#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr19(Arguments /* args */)
{
	abort("Interrupt 19 caught!\n");
}

} // namespace isr
