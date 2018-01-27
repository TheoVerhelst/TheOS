#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr62(Arguments /* args */)
{
	abort("Interrupt 62 caught!\n");
}

} // namespace isr
