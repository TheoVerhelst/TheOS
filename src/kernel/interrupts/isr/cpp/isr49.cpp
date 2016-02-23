#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr49(Arguments /* args */)
{
	abort("Interrupt 49 caught!\n");
}

}// namespace isr
