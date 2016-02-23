#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr48(Arguments /* args */)
{
	abort("Interrupt 48 caught!\n");
}

}// namespace isr
