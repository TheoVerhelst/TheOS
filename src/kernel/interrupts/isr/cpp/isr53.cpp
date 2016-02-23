#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr53(Arguments /* args */)
{
	abort("Interrupt 53 caught!\n");
}

}// namespace isr
