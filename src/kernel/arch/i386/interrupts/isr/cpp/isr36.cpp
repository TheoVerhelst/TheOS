#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr36(Arguments /* args */)
{
	abort("Interrupt 36 caught!\n");
}

} // namespace isr
