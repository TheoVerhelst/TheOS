#include <kernel/Kernel.hpp>
#include <kernel/gdt.hpp>
#include <kernel/interrupts/idt.hpp>
#include <kernel/interrupts/pic.hpp>

extern "C" void kernelMain()
{
    gdt::initializeGdt();
    idt::initializeIdt();
    pic::initializePic();
    Kernel kernel;
	kernel.run();
}
