#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr44(Arguments /* args */)
{
	abort("Interrupt 44 caught!\n");
}

}// namespace isr
