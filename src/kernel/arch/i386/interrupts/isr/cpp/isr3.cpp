#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr3(Arguments /* args */)
{
	abort("Interrupt 3 caught!\n");
}

} // namespace isr
