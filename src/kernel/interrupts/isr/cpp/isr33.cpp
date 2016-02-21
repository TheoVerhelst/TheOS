#include <kernel/ps2/KeyboardDriver.hpp>
#include <kernel/interrupts/isr/isr33.hpp>

void isr33cpp(isr::IsrArgs args)
{
	ps2::keyboardDriver.pollKeyboard();
}
