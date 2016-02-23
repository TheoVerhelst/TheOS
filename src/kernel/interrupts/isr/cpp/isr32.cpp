#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr32(Arguments /* args */)
{
	abort("Interrupt 32 caught!\n");
}

}// namespace isr
