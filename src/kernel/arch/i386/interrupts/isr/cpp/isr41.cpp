#include <cpp/abort.hpp>
#include <cpp/log.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr41(Arguments& args)
{
	LOG(Severity::Error) << "Registers dump: " << args << "\n";
	abort("Interrupt 41 caught!\n");
}

} // namespace isr
