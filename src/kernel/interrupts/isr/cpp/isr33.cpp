#include <kernel/Kernel.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr33(Arguments /* args */)
{
	Kernel::getInstance()._keyboardDriver.pollKeyboard();
}

}// namespace isr
