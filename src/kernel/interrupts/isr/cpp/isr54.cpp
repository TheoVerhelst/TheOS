#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr54(Arguments /* args */)
{
	abort("Interrupt 54 caught!\n");
}

} // namespace isr
