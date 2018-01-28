#include <cpp/abort.hpp>
#include <cpp/log.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr38(Arguments& args)
{
	LOG(Severity::Error) << "Registers dump: " << args << "\n";
	abort("Interrupt 38 caught!\n");
}

} // namespace isr
