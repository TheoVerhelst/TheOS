#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr13(Arguments /* args */)
{
	abort("Interrupt 13 caught!\n");
}

} // namespace isr
