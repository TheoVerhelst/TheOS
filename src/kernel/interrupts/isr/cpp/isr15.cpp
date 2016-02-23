#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr15(Arguments /* args */)
{
	abort("Interrupt 15 caught!\n");
}

}// namespace isr
