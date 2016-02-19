#include <io/in.hpp>
#include <io/out.hpp>
#include <io/ioWait.hpp>
#include <kernel/interrupts/PIC.hpp>

namespace pic
{

void initializePic()
{
	remap();
	// Enable interrupts
	asm volatile("sti");
}

void sendEndOfInterrupt(unsigned char irq)
{
	if(irq >= slaveOffset)
		outb(slaveCommand, Command::EndOfInterrupt);

	outb(masterCommand, Command::EndOfInterrupt);
}

void remap()
{
	// Save masks
	const uint8_t masterMask{inb(masterData)};
	const uint8_t slaveMask{inb(slaveData)};

	// Send ICW1
	outb(masterCommand, Command::Init | Command::RequireIcw4);
	outb(slaveCommand, Command::Init | Command::RequireIcw4);

	// Send ICW2
	outb(masterData, masterOffset);
	outb(slaveData, slaveOffset);

	// Send ICW3
	outb(masterData, 1 << 2);// tell master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(slaveData, 1 << 1);// tell slave PIC its cascade identity (0000 0010)

	// Send ICW4
	outb(masterData, InitCommandWord4::Mode8086);
	outb(slaveData, InitCommandWord4::Mode8086);

	// Restore saved masks
	outb(masterData, masterMask);
	outb(slaveData, slaveMask);
}

}// namespace pic

