#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/pic.hpp>
#include <boot/MultibootInfo.hpp>
#include <boot/MemoryMap.hpp>
#include <kernel/Kernel.hpp>

extern "C" void kernelMain(const multiboot::MultibootInfo& multibootInfoAddress)
{
    idt::initializeIdt();
    pic::initializePic();
    const MemoryMap memoryMap{multibootInfoAddress};
    Kernel kernel{multibootInfoAddress};
	kernel.run();
}
