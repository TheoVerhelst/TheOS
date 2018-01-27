#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr18(Arguments /* args */)
{
	abort("Interrupt 18 caught!\n");
}

} // namespace isr
