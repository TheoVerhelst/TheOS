#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr48(Arguments /* args */)
{
	abort("Interrupt 48 caught!\n");
}

} // namespace isr
