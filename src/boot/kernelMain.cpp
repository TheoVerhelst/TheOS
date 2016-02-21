#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

#include <kernel/Kernel.hpp>
#include <boot/Icxxabi.hpp>

extern "C" void kernelMain()
{
	kernel.run();
	// Call destructors, in doubt
	__cxa_finalize(0);
}
