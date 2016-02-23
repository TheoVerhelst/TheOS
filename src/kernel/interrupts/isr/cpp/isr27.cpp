#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr27(Arguments /* args */)
{
	abort("Interrupt 27 caught!\n");
}

}// namespace isr
