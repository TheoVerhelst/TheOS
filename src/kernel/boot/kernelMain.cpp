#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/pic.hpp>
#include <kernel/multiboot/MultibootInfo.hpp>
#include <kernel/multiboot/MemoryMap.hpp>
#include <kernel/Kernel.hpp>

extern "C" void kernelMain(const multiboot::MultibootInfo& multibootInfoAddress)
{
    idt::initializeIdt();
    pic::initializePic();
    const multiboot::MemoryMap memoryMap{multibootInfoAddress};
    Kernel kernel{memoryMap};
    kernel.run();
}
