#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

#include <stdio.hpp>
#include <kernel/terminal/Terminal.hpp>

Terminal terminal;

extern "C" void kernel_main()
{
	printf("Veuillez patienter...");
}
