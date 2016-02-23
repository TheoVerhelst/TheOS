#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr6(Arguments /* args */)
{
	abort("Interrupt 6 caught!\n");
}

}// namespace isr
