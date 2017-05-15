#include <kernel/io.hpp>
#include <kernel/interrupts/pic.hpp>

namespace pic
{

void initializePic()
{
	remap();
	// Enable interrupts
	asm volatile("sti");
}

void sendEndOfInterrupt(uint32_t interruptNumber)
{
	if(interruptNumber >= slaveOffset)
		outb(slaveCommand, Command::EndOfInterrupt);

	outb(masterCommand, Command::EndOfInterrupt);
}

void remap()
{
	// Send ICW1
	outb(masterCommand, Command::Init | Command::RequireIcw4);
	outb(slaveCommand, Command::Init | Command::RequireIcw4);

	// Send ICW2
	outb(masterData, masterOffset);
	outb(slaveData, slaveOffset);

	// Send ICW3
	outb(masterData, MasterInterrupMask::Cascade);// tell master PIC that there is a slave PIC
	outb(slaveData, SlaveInterruptMask::CascadeIdentity);// tell slave PIC its cascade identity

	// Send ICW4
	outb(masterData, InitCommandWord4::Mode8086);
	outb(slaveData, InitCommandWord4::Mode8086);

	// Only enable keyboard
   outb(masterData, ~MasterInterrupMask::Keyboard);
   outb(slaveData, ~UINT8_C(0));
}

} // namespace pic

