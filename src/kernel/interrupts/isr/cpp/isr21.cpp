#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr21(Arguments /* args */)
{
	abort("Interrupt 21 caught!\n");
}

}// namespace isr
