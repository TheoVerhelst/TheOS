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
    char kernelObject[sizeof(Kernel)];
    Kernel::_instance = reinterpret_cast<Kernel*>(&kernelObject);
    new (static_cast<void*>(&kernelObject)) Kernel(memoryMap);
	Kernel::_instance->run();
}
