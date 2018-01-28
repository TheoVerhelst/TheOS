#include <cpp/abort.hpp>
#include <cpp/log.hpp>
#include <kernel/arch/i386/interrupts/isr.hpp>

namespace isr
{

void Table::isr14(Arguments& args)
{
	PageFaultErrorCode& errorCode{reinterpret_cast<PageFaultErrorCode&>(args.errorCode)};
	uint32_t faultAddress;
	asm volatile("movl %%cr2, %0" : "=r"(faultAddress));
	out << Printer::Flags::ShowBase;
	LOG(Severity::Error) << "Content of the flags: " << Printer::Flags::Bin << errorCode.flags << "\n";
	LOG(Severity::Error) << "Faulting address:     " << Printer::Flags::Hex << faultAddress << "\n";
	LOG(Severity::Error) << args;
	abort("Interrupt 14 caught\n");
}

} // namespace isr
