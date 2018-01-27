#include <kernel/arch/i386/interrupts/idt.hpp>
#include <kernel/arch/i386/interrupts/pic.hpp>
#include <kernel/multiboot/MultibootInfo.hpp>
#include <kernel/multiboot/MemoryMap.hpp>
#include <kernel/Kernel.hpp>

extern "C" void kernelMain(const multiboot::MultibootInfo& multibootInfoAddress)
{
    idt::initializeIdt();
    pic::initializePic();
    // Here we instantiate the keyboard driver. It is implemented by a PS/2 one
    // on this architecture, but it could be another implementation (serial port
    // for example).
    ps2::KeyboardDriver keyboardDriver;
    // The memory map is not abstracted like keyboard driver, since we assume,
    // for now, that we'll always be loaded by a multiboot-compliant loader. So
    // the memory map will always be a multiboot memory map.
    const multiboot::MemoryMap memoryMap{multibootInfoAddress};
    Kernel kernel{memoryMap, keyboardDriver};
    kernel.run();
}
