#ifndef PIC_HPP
#define PIC_HPP

#include <cstdint>

namespace pic
{

constexpr uint16_t masterAddress{0x20};///< IO base address for master PIC
constexpr uint16_t slaveAddress{0xA0}; ///< IO base address for slave PIC
constexpr uint16_t masterCommand{masterAddress};
constexpr uint16_t masterData{masterAddress + 1};
constexpr uint16_t slaveCommand{slaveAddress};
constexpr uint16_t slaveData{slaveAddress + 1};
constexpr uint8_t masterOffset{0x20};
constexpr uint8_t slaveOffset{0x28};

enum Command : uint8_t
{
	RequireIcw4    = 1 << 0,
	Single         = 1 << 1,
	Interval4      = 1 << 2,
	Level          = 1 << 3,
	Init           = 1 << 4,
	EndOfInterrupt = 1 << 5
};

enum InitCommandWord4 : uint8_t
{
	Mode8086           = 1 << 0,             ///< 8086/88 (MCS-80/85) mode.
	AutoEndOfInterrupt = 1 << 1,             ///< Auto (normal) EOI.
	BufferedMaster     = (1 << 2) | (1 << 3),///< Buffered mode master
	BufferedSlave      = 1 << 3,             ///< Buffered mode slave.
	SpecialFullyNested = 1 << 4,             ///< Special fully nested.
};

enum MasterInterrupMask : uint8_t
{
	Timer      = 1 << 0,
	Keyboard   = 1 << 1,
	Cascade    = 1 << 2,
	Com2       = 1 << 3,
	Com1       = 1 << 4,
	Lpt2       = 1 << 5,
	FloppyDisk = 1 << 6,
	Lpt1       = 1 << 7
};

enum SlaveInterruptMask : uint8_t
{
	CmosClock       = 1 << 0,
	FreeIrq1        = 1 << 1,
	FreeIrq2        = 1 << 2,
	FreeIrq3        = 1 << 3,
	Ps2Mouse        = 1 << 4,
	Fpu             = 1 << 5,
	PrimaryAtaHdd   = 1 << 6,
	SecondaryAtaHdd = 1 << 7,
};

void initializePic();

void sendEndOfInterrupt(uint32_t interruptNumber);

void remap();

}// namespace pic

#endif// PIC_HPP
