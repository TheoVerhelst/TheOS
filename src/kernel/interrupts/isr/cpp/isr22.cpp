#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr22(Arguments /* args */)
{
	abort("Interrupt 22 caught!\n");
}

} // namespace isr
