#include <cpp/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr4(Arguments /* args */)
{
	abort("Interrupt 4 caught!\n");
}

} // namespace isr
