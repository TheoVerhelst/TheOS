#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr61(Arguments /* args */)
{
	abort("Interrupt 61 caught!\n");
}

} // namespace isr
