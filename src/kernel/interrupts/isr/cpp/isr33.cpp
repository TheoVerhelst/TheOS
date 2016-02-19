#include <Printer.hpp>
#include <io/in.hpp>
#include <kernel/interrupts/isr/isr33.hpp>

void isr33cpp(isr::IsrArgs args)
{
	out << "Key pressed or released!\n";
	inb(0x60);
}
