#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr21(Arguments /* args */)
{
	abort("Interrupt 21 caught!\n");
}

} // namespace isr
