#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr31(Arguments /* args */)
{
	abort("Interrupt 31 caught!\n");
}

} // namespace isr
