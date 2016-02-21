#include <kernel/Kernel.hpp>

void Kernel::isr33(isr::IsrArgs args)
{
	_keyboardDriver.pollKeyboard();
}
