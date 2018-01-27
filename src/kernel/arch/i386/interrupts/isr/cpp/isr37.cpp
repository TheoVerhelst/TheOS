#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr37(Arguments /* args */)
{
	abort("Interrupt 37 caught!\n");
}

} // namespace isr
