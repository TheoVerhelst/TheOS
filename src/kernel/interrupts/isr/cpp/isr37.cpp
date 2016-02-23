#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr37(Arguments /* args */)
{
	abort("Interrupt 37 caught!\n");
}

}// namespace isr
