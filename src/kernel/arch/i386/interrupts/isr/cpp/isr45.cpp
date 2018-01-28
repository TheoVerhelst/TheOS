#include <cpp/abort.hpp>
#include <cpp/log.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr45(Arguments& args)
{
	LOG(Severity::Error) << "Registers dump: " << args << "\n";
	abort("Interrupt 45 caught!\n");
}

} // namespace isr
