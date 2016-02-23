#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr29(Arguments /* args */)
{
	abort("Interrupt 29 caught!\n");
}

}// namespace isr
