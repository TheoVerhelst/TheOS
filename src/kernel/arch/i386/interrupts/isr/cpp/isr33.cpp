#include <kernel/Kernel.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr33(Arguments& /* args */)
{
	Kernel::getInstance()._keyboardDriver.pollKeyboard();
}

} // namespace isr
