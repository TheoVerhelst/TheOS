#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr49(Arguments /* args */)
{
	abort("Interrupt 49 caught!\n");
}

} // namespace isr
