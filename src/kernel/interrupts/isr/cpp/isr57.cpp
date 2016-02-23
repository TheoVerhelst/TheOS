#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr57(Arguments /* args */)
{
	abort("Interrupt 57 caught!\n");
}

}// namespace isr
