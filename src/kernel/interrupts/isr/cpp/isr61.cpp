#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr61(Arguments /* args */)
{
	abort("Interrupt 61 caught!\n");
}

} // namespace isr
