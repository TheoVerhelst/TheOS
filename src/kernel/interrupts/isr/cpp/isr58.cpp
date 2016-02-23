#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr58(Arguments /* args */)
{
	abort("Interrupt 58 caught!\n");
}

}// namespace isr
