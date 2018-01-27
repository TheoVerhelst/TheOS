#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr13(Arguments /* args */)
{
	abort("Interrupt 13 caught!\n");
}

} // namespace isr
