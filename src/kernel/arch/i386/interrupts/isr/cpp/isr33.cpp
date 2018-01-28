#include <kernel/Kernel.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr33(Arguments& /* args */)
{
	Kernel* kernel{&Kernel::getInstance()};
	// If this interrupt is called before the kernel is fully initialized, then
	// it will be nullptr.
	if(kernel != nullptr)
		kernel->_keyboardDriver.pollKeyboard();
}

} // namespace isr
