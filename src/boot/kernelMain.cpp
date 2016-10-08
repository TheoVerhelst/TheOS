#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i386-elf to work properly!"
#endif

#include <kernel/Kernel.hpp>
#include <boot/Icxxabi.hpp>

extern "C" void kernelMain()
{
	kernel.run();
}
