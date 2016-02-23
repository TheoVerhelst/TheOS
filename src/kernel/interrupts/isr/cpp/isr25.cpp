#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr25(Arguments /* args */)
{
	abort("Interrupt 25 caught!\n");
}

}// namespace isr
