#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr51(Arguments /* args */)
{
	abort("Interrupt 51 caught!\n");
}

} // namespace isr
