#ifndef PIC_HPP
#define PIC_HPP

#include <cstdint>

/// \addtogroup Kernel
/// \{

/// Objects related to the Programmable Interrupt Controller (PIC). The PIC is
/// an hardware device that manages the interrupts before passing them to the
/// CPU. And this device is programmable by the OS, and this namespace holds
/// things useful for this programmation.
namespace pic
{

/// IO base address for master PIC.
constexpr uint16_t masterAddress{0x20};

/// IO base address for slave PIC.
constexpr uint16_t slaveAddress{0xA0};

/// IO address to use when sending commands to the master PIC.
constexpr uint16_t masterCommand{masterAddress};

/// IO address to use when sending data to the master PIC.
constexpr uint16_t masterData{masterAddress + 1};

/// IO address to use when sending commands to the slave PIC.
constexpr uint16_t slaveCommand{slaveAddress};

/// IO address to use when sending data to the slave PIC.
constexpr uint16_t slaveData{slaveAddress + 1};

/// Index of the first interrupt sent by the master PIC in the IDT.
constexpr uint8_t masterOffset{0x20};

/// Index of the first interrupt sent by the slave PIC in the IDT.
constexpr uint8_t slaveOffset{0x28};

/// Namespace for the enumeration of the commands that can be sent to the PIC.
namespace Command
{

/// Enumeration of the commands that can be sent to the PIC.
enum Command : uint8_t
{
	RequireIcw4    = 1 << 0,
	Single         = 1 << 1,
	Interval4      = 1 << 2,
	Level          = 1 << 3,
	Init           = 1 << 4,
	EndOfInterrupt = 1 << 5
};

}// namespace Command

namespace InitCommandWord4
{

enum InitCommandWord4 : uint8_t
{
	Mode8086           = 1 << 0,             ///< 8086/88 (MCS-80/85) mode.
	AutoEndOfInterrupt = 1 << 1,             ///< Auto (normal) EOI.
	BufferedMaster     = (1 << 2) | (1 << 3),///< Buffered mode master
	BufferedSlave      = 1 << 3,             ///< Buffered mode slave.
	SpecialFullyNested = 1 << 4,             ///< Special fully nested.
};

}// namespace InitCommandWord4

namespace MasterInterrupMask
{

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

}// namespace MasterInterrupMask

namespace SlaveInterruptMask
{

enum SlaveInterruptMask : uint8_t
{
	CmosClock       = 1 << 0,
	CascadeIdentity = 1 << 1,
	FreeIrq2        = 1 << 2,
	FreeIrq3        = 1 << 3,
	Ps2Mouse        = 1 << 4,
	Fpu             = 1 << 5,
	PrimaryAtaHdd   = 1 << 6,
	SecondaryAtaHdd = 1 << 7,
};

}// namespace SlaveInterruptMask

void initializePic();

void sendEndOfInterrupt(uint32_t interruptNumber);

void remap();

}// namespace pic

/// \}

#endif// PIC_HPP
