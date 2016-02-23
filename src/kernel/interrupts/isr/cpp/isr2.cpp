#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr2(Arguments /* args */)
{
	abort("Interrupt 2 caught!\n");
}

}// namespace isr
