#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr53(Arguments /* args */)
{
	abort("Interrupt 53 caught!\n");
}

} // namespace isr
