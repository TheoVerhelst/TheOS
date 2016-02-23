#include <kernel/abort.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr41(Arguments /* args */)
{
	abort("Interrupt 41 caught!\n");
}

}// namespace isr
