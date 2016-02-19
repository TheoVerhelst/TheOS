#include <io/in.hpp>
#include <io/out.hpp>
#include <io/ioWait.hpp>
#include <kernel/interrupts/PIC.hpp>

namespace pic
{

void initializePic()
{
	remap();
}

void sendEndOfInterrupt(unsigned char irq)
{
	if(irq >= 8)
		outb(slaveCommand, Command::EndOfInterrupt);

	outb(masterCommand, Command::EndOfInterrupt);
}

void remap()
{
	const uint8_t masterMask{inb(masterData)};// save masks
	const uint8_t slaveMask{inb(slaveData)};

	// starts the initialization sequence (in cascade mode)
	outb(masterCommand, Command::Init | Command::RequireIcw4);
	ioWait();
	outb(slaveCommand, Command::Init | Command::RequireIcw4);
	ioWait();
	outb(masterData, masterOffset);// ICW2: master PIC vector offset
	ioWait();
	outb(slaveData, slaveOffset);// ICW2: slave PIC vector offset
	ioWait();
	outb(masterData, 1 << 2);// ICW3: tell master PIC that there is a slave PIC at IRQ2 (0000 0100)
	ioWait();
	outb(slaveData, 1 << 1);// ICW3: tell slave PIC its cascade identity (0000 0010)
	ioWait();

	outb(masterData, InitCommandWord4::Mode8086);
	ioWait();
	outb(slaveData, InitCommandWord4::Mode8086);
	ioWait();

	outb(masterData, masterMask);// restore saved masks.
	outb(slaveData, slaveMask);
}

}// namespace pic

