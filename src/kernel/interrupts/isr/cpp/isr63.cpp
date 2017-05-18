#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr63(Arguments /* args */)
{
	abort("Interrupt 63 caught!\n");
}

} // namespace isr
