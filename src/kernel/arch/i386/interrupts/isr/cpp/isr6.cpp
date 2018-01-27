#include <cpp/abort.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr6(Arguments /* args */)
{
	abort("Interrupt 6 caught!\n");
}

} // namespace isr
