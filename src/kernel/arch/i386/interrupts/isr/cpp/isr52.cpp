#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr52(Arguments /* args */)
{
	abort("Interrupt 52 caught!\n");
}

} // namespace isr
