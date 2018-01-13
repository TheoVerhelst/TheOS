#include <cpp/abort.hpp>
#include <cpp/Printer.hpp>
#include <kernel/interrupts/isr.hpp>

namespace isr
{

void Table::isr14(Arguments args)
{
	out << args.errorCode << "\nAt " << Printer::Flags::Hex << args.eip << "\n";
	abort("Interrupt 14 caught!\n");
}

} // namespace isr
