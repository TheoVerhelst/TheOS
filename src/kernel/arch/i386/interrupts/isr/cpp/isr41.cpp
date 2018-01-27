#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr41(Arguments /* args */)
{
	abort("Interrupt 41 caught!\n");
}

} // namespace isr
