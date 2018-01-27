#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr27(Arguments /* args */)
{
	abort("Interrupt 27 caught!\n");
}

} // namespace isr
