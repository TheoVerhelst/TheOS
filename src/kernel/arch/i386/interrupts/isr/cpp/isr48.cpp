#include <cpp/abort.hpp>
#include <cpp/log.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr48(Arguments& args)
{
	LOG(Severity::Error) << "Registers dump: " << args << "\n";
	abort("Interrupt 48 caught!\n");
}

} // namespace isr
